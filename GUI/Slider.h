#include "MenuController.h"

void MoveIndicators();

class Slider
{
private:
    sf::RenderWindow *window;

    sf::RectangleShape rect;
    Button             indicator;

    float width;
    float height;

    float widthIndicator;
    float heightIndicator;

    float minValue;
    float maxValue;

    sf::Vector2f indicatorPosition = {0, 0};

public:
    Slider(float width = 400, float height = 50, float minValue = 0, float maxValue = 100);

    void SetWindow    (sf::RenderWindow *window);
    void MoveIndicator();
    void Show();
};

static std::vector<Slider*> sliders;

//-----------------------------------------------------------------------------
//{     Slider realization
//-----------------------------------------------------------------------------

Slider::Slider(float width, float height, float minValue, float maxValue)
{
    this->width    = width;
    this->height   = height;
    this->minValue = width;
    this->maxValue = width;

    widthIndicator  = width / 10;
    heightIndicator = height;

    rect.     setSize({ width,          height });
    indicator.SetSize({ widthIndicator, height });

    indicator.SetFillColor(sf::Color::Red);

    sliders.push_back(this);
}

//-----------------------------------------------------------------------------

void Slider::SetWindow(sf::RenderWindow *window)
{
    this->window = window;
}

//-----------------------------------------------------------------------------

void Slider::MoveIndicator()
{
    static bool  buttonIsPressed = false;
    static float dist = 0;

    sf::Vector2f cursorPosition = GetCursorPosition(*window);

    if(indicator.IsPressed(*window) && !buttonIsPressed)
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

    indicator.SetPosition(indicatorPosition);
}

//-----------------------------------------------------------------------------

void Slider::Show()
{
    window->draw(rect);
    indicator.Show(*window);
}

//-----------------------------------------------------------------------------
//}     End Slider
//-----------------------------------------------------------------------------

void MoveIndicators()
{
    int sliderSize = sliders.size();
    for(int i = 0; i < sliderSize; i++)
    {
        sliders[i]->MoveIndicator();
    }
}

//-----------------------------------------------------------------------------
