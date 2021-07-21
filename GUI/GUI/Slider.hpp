#ifndef SLIDER
#define SLIDER

#include "Button.hpp"

//-----------------------------------------------------------------------------

void ControllSliders();

//-----------------------------------------------------------------------------

class Slider
{
private:
    sf::RenderWindow *window = 0;

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
    Slider(float width          = 400, float height          = 4,
           float widthIndicator = 13,  float heightIndicator = 40,
           float minValue       = 0,   float maxValue        = 1);

    void moveIndicator();
    void draw         (sf::RenderWindow &window);

    void setPosition         (sf::Vector2f position);
    void setRectSize         (sf::Vector2f size);
    void setIndicatorSize    (sf::Vector2f size);
    void setRectColor        (sf::Color    color);
    void setChangingRectColor(sf::Color    color);
    void setIndicatorColor   (sf::Color    color);
    void setScale            (sf::Vector2f scale);
    void setInterval         (float        minValue, float maxValue);
    void setValue            (float        value);

    float        getValue();
    sf::Vector2f getRectSize();
    sf::Vector2f getIndicatorSize();
    sf::Vector2f getScale();
    sf::Vector2f getPosition();
};

static std::vector<Slider*> sliders;

//-----------------------------------------------------------------------------
//{     Slider realization
//-----------------------------------------------------------------------------

//{     Private Functions

void Slider::setIndicatorPosition()
{
    sf::Vector2f indicatorPosition = indicator.getPosition() ;
    sf::Vector2f rectPosition      = rect.     getPosition();
    sf::Vector2f scale             = rect.     getScale();

    indicatorPosition.y  = rectPosition.y - (heightIndicator - height) / 2 * scale.y;
    indicatorPosition.x += rectPosition.x;
    indicatorPosition.x /= scale.x;

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

    sf::Vector2f scale             = rect.getScale();
    sf::Vector2f cursorPosition    = GetCursorPosition(*window);
    sf::Vector2f indicatorPosition = indicator.getPosition();

    if(indicator.isPressed())
    {
        if(!buttonIsPressed)
        {
            dist = cursorPosition.x - indicatorPosition.x;

            buttonIsPressed = true;
        }

        indicatorPosition.x = cursorPosition.x - dist;

        sf::Vector2f rectPosition = rect.getPosition();;

        if     (indicatorPosition.x < rectPosition.x)
        {
            indicatorPosition.x = rectPosition.x;
        }
        else if(indicatorPosition.x > rectPosition.x + (width - widthIndicator) * scale.x)
        {
            indicatorPosition.x = rectPosition.x + (width - widthIndicator) * scale.x;
        }
    }
    else
    {
        buttonIsPressed = false;
    }

    indicator.setPosition(indicatorPosition);

    rectChanging.setSize({ (indicatorPosition.x - rect.getPosition().x) / scale.x, height });
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

void Slider::setPosition(sf::Vector2f position)
{
    rect.        setPosition(position);
    rectChanging.setPosition(position);

    setIndicatorPosition();
}

//-----------------------------------------------------------------------------

void Slider::setRectSize(sf::Vector2f size)
{
    sf::Vector2f rectChangingSize = rectChanging.getSize();

    float k = rectChangingSize.x / width;

    width  = size.x;
    height = size.y;

    if(width / 2 < widthIndicator)  width  = widthIndicator;
    if(height    > heightIndicator) height = heightIndicator;

    rect.        setSize({ width,     height });
    rectChanging.setSize({ width * k, height });

    setIndicatorPosition();
}

//-----------------------------------------------------------------------------

void Slider::setRectColor(sf::Color color)
{
    rect.setFillColor(color);
}

//-----------------------------------------------------------------------------

void Slider::setChangingRectColor(sf::Color color)
{
    rectChanging.setFillColor(color);
}

//-----------------------------------------------------------------------------

void Slider::setIndicatorColor(sf::Color color)
{
    indicator.setFillColor(color);
}

//-----------------------------------------------------------------------------

void Slider::setIndicatorSize(sf::Vector2f size)
{
    if(size.x > width / 2)  size.x = width / 2;
    if(size.y < height)     size.y = height;

    indicator.setSize(size);

    widthIndicator  = size.x;
    heightIndicator = size.y;

    setIndicatorPosition();
}

//-----------------------------------------------------------------------------

void Slider::setScale(sf::Vector2f scale)
{
    rect.        setScale(scale);
    rectChanging.setScale(scale);
    indicator   .setScale(scale);

    setIndicatorPosition();
}

//-----------------------------------------------------------------------------

void Slider::setInterval(float minValue, float maxValue)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

//-----------------------------------------------------------------------------

void Slider::setValue(float value)
{
    sf::Vector2f scale        = rect.getScale   ();
    sf::Vector2f rectPosition = rect.getPosition();

    if(value > maxValue) value = maxValue;
    if(value < minValue) value = minValue;

    float k = (value - minValue) / (maxValue - minValue);

    sf::Vector2f indicatorPosition = indicator.getPosition();

    indicatorPosition.x = rectPosition.x + (width - widthIndicator) * scale.x * k;

    indicator.setPosition(indicatorPosition);
}

//-----------------------------------------------------------------------------

float Slider::getValue()
{
    sf::Vector2f scale             = rect.     getScale   ();
    sf::Vector2f indicatorPosition = indicator.getPosition();
    sf::Vector2f rectPosition      = rect.     getPosition();

    float value = (indicatorPosition.x - rectPosition.x) / (width - widthIndicator) / scale.x;

    return value * (maxValue - minValue) + minValue;
}

//-----------------------------------------------------------------------------

sf::Vector2f Slider::getRectSize()
{
    return rect.getSize();
}

//-----------------------------------------------------------------------------

sf::Vector2f Slider::getIndicatorSize()
{
    return indicator.getSize();
}

//-----------------------------------------------------------------------------

sf::Vector2f Slider::getScale()
{
    return rect.getScale();
}

//-----------------------------------------------------------------------------

sf::Vector2f Slider::getPosition()
{
    return rect.getPosition();
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

#endif
