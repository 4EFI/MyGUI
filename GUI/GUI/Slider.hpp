#include "Button.hpp"

void ControllSliders();

class Slider
{
private:
    sf::RenderWindow *window = NULL;

    sf::RectangleShape rect;
    sf::RectangleShape rectChanging;
    Button             indicator;

    float width;
    float height;

    float widthIndicator;
    float heightIndicator;

    float minValue;
    float maxValue;

    void setIndicatorPosition();

public:
    Slider(float width          = 400, float height          = 5,
           float widthIndicator = 17,  float heightIndicator = 45,
           float minValue       = 0,   float maxValue        = 100);

    void moveIndicator();
    void draw         (sf::RenderWindow &window);

    void setRectSize(sf::Vector2f size);

    float getValue();
};

static std::vector<Slider*> sliders;

//-----------------------------------------------------------------------------
//{     Slider realization
//-----------------------------------------------------------------------------

//{     Private Functions

void Slider::setIndicatorPosition()
{
    sf::Vector2f indicatorPosition = indicator.getPosition();
    sf::Vector2f rectPosition      = rect.     getPosition();

    indicatorPosition.y = rectPosition.y - (heightIndicator - height) / 2;

    indicator.setPosition(indicatorPosition);
}

//}     End of Private Functions

//{     Public Functions

Slider::Slider(float width,          float height,
               float widthIndicator, float heightIndicator,
               float minValue,       float maxValue)
{
    this->width    = width;
    this->height   = height;
    this->minValue = width;
    this->maxValue = width;

    this->widthIndicator  = widthIndicator;
    this->heightIndicator = heightIndicator;

    this->minValue = minValue;
    this->maxValue = maxValue;

    rect.     setSize({ width,          height });
    indicator.setSize({ widthIndicator, heightIndicator });

    rectChanging.setSize({0, height});

    rectChanging.setFillColor(sf::Color::Red);
    indicator.   setFillColor(sf::Color::Red);

    sf::Vector2f rectPosition = { 0, (heightIndicator - height) / 2 };

    rect.        setPosition(rectPosition);
    rectChanging.setPosition(rectPosition);

    sliders.push_back(this);
}

//-----------------------------------------------------------------------------

void Slider::moveIndicator()
{
    if(window == NULL) return;

    static bool  buttonIsPressed = false;
    static float dist = 0;

    sf::Vector2f cursorPosition    = GetCursorPosition(*window);
    sf::Vector2f indicatorPosition = indicator.getPosition();

    if(indicator.isPressed(*window) && !buttonIsPressed)
    {
        buttonIsPressed = true;

        dist = cursorPosition.x - indicatorPosition.x;
    }

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        buttonIsPressed = false;
    }

    if(buttonIsPressed)
    {
        indicatorPosition.x = cursorPosition.x - dist;

        sf::Vector2f rectPosition = rect.getPosition();;

        if     (indicatorPosition.x < rectPosition.x)
        {
            indicatorPosition.x = rectPosition.x;
        }
        else if(indicatorPosition.x > rectPosition.x + width - widthIndicator)
        {
            indicatorPosition.x = rectPosition.x + width - widthIndicator;
        }
    }

    indicator.setPosition(indicatorPosition);

    rectChanging.setSize({ indicatorPosition.x - rect.getPosition().x, height });
}

//-----------------------------------------------------------------------------

void Slider::draw(sf::RenderWindow &window)
{
    this->window = &window;

    this->window->draw(rect);
    this->window->draw(rectChanging);

    indicator.draw(window);
}

//-----------------------------------------------------------------------------

void Slider::setRectSize(sf::Vector2f size)
{
    sf::Vector2f rectChangingSize = rectChanging.getSize();

    float k = rectChangingSize.x / width;

    width  = size.x;
    height = size.y;

    if(width  < widthIndicator)  width  = widthIndicator;
    if(height > heightIndicator) height = heightIndicator;

    rect.        setSize({ width,     height });
    rectChanging.setSize({ width * k, height });

    setIndicatorPosition();
}

//-----------------------------------------------------------------------------

float Slider::getValue()
{
    sf::Vector2f indicatorPosition = indicator.getPosition();
    sf::Vector2f rectPosition      = rect.     getPosition();

    float value = (indicatorPosition - rectPosition).x / (width - widthIndicator);

    return value * (maxValue - minValue) + minValue;
}

//}     End of Public Functions

//-----------------------------------------------------------------------------
//}     End Slider
//-----------------------------------------------------------------------------

void ControllSliders()
{
    int sliderSize = sliders.size();
    for(int i = 0; i < sliderSize; i++)
    {
        sliders[i]->moveIndicator();
    }
}

//-----------------------------------------------------------------------------