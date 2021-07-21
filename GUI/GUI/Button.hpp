#ifndef BUTTON
#define BUTTON

#include "SFML/Graphics.hpp"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <float.h>
#include <vector>
#include "Tools.hpp"

//-----------------------------------------------------------------------------

#define DEFAULT_BUTTON "Textures\\DefaultButton.png"

//-----------------------------------------------------------------------------

class Button
{
protected:
    sf::RectangleShape rectangle;
    sf::Texture        buttonTexture;

    sf::RectangleShape rectChoose;

    sf ::Font   fontText;
    std::string textStr;
    sf ::Text   startText;
    sf ::Text   text;

    bool isLeftButtonPressed = false;
    bool isInsideRect        = true;

    sf::RenderWindow *window = 0;

    float maxLengthText = FLT_MAX;

    void setTextPosition();
    void setTextHeight();

public:
    Button();

    void draw     (sf::RenderWindow &window);
    bool isPressed();
    bool isClicked();

    void isCursorInsideBox();

    void move          (sf::Vector2f      position);
    void setTexture    (sf::Texture       texture);
    void setTextureRect(sf::IntRect       rect);
    void setWindow     (sf::RenderWindow &window);
    void setScale      (sf::Vector2f      scale);
    void setSize       (sf::Vector2f      size);
    void setPosition   (sf::Vector2f      position);
    void setFillColor  (sf::Color         color);
    void setTextString (std::string       str);
    void setTextLength (float             length);
    void setVisible    (float             visible);

    sf::Vector2f getPosition();
    sf::Vector2f getSize    ();
    sf::Vector2f getScale   ();
};

//-----------------------------------------------------------------------------
//{     Button realization
//-----------------------------------------------------------------------------

/*!
\defgroup main_module Main Module
*/

Button::Button()
{
    rectangle.setSize({200, 100});

    fontText.loadFromFile("Fonts\\ariblk.ttf");
    text.setFont(fontText);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
}

//-----------------------------------------------------------------------------

void Button::setTextPosition()
{
    sf::Vector2f positionRect = rectangle.getPosition();
    sf::Vector2f scaleRect    = rectangle.getScale();
    sf::Vector2f sizeRect     = rectangle.getSize();

    sizeRect = { sizeRect.x * scaleRect.x, sizeRect.y * scaleRect.y };

    sf::FloatRect textBounds = text.getLocalBounds();

    textBounds.width  *= scaleRect.x;
    textBounds.height *= scaleRect.y;
    textBounds.left   *= scaleRect.x;
    textBounds.top    *= scaleRect.y;

    text.setPosition((sizeRect.x - textBounds.width)  / 2 + positionRect.x - textBounds.left,
                     (sizeRect.y - textBounds.height) / 2 + positionRect.y - textBounds.top);
}

//-----------------------------------------------------------------------------

void Button::setTextHeight()
{
    sf::Vector2f positionRect = rectangle.getPosition();
    sf::Vector2f scaleRect    = rectangle.getScale();
    sf::Vector2f sizeRect     = rectangle.getSize();

    sf::FloatRect textBounds = this->text.getLocalBounds();

    if(textBounds.height > sizeRect.y)
    {
        int sizeText = text.getCharacterSize();
        text.setCharacterSize(int(sizeText / textBounds.height * sizeRect.y - 5));
    }
}

//-----------------------------------------------------------------------------

/*! \addtogroup main_module @{ */

/*!

\brief Function that displays a button on the window

\param window The window where the button will be displayed

Example using
\code
    int main()
    {
        sf::RenderWindow window(sf::VideoMode(1000, 700), "Example");

        Button button;

        while(true)
        {
            window.clear();

            button.draw(window);

            window.display();
        }
    }
\endcode

*/

void Button::draw(sf::RenderWindow &window)
{
    this->window = &window;

    window.draw(rectangle);

    window.draw(text);

    isCursorInsideBox();
}

//-----------------------------------------------------------------------------

/*!

\brief Function shows if the button is pressed

\param window The window where the button press will be read

\return TRUE - the button is pressed else - FALSE

Example using
\code
    Button button;

    if(button.isPressed(window))
    {
        ...
    }
\endcode

*/

bool Button::isPressed()
{
    if(window == NULL) return 0;

    sf::Vector2f cursorPosition = GetCursorPosition(*window);
    sf::Vector2f buttonPosition = rectangle.getPosition();
    sf::Vector2f scale          = rectangle.getScale();

    sf::Vector2u sizeButton = { rectangle.getSize().x * scale.x,
                                rectangle.getSize().y * scale.y };

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(!IsInsideRect(cursorPosition, &rectangle) && !isLeftButtonPressed)
        {
            isInsideRect = false;
        }

        isLeftButtonPressed = true;
    }
    else
    {
        isLeftButtonPressed = false;
        isInsideRect        = true;

        return 0;
    }

    if(!isInsideRect) return 0;

    return 1;
}

//-----------------------------------------------------------------------------

bool Button::isClicked()
{
    if(window == NULL) return 0;

    if(!isLeftButtonPressed & isPressed())
    {
        return 1;
    }

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        isLeftButtonPressed = false;
    }

    return 0;
}

//-----------------------------------------------------------------------------

void Button::isCursorInsideBox()
{
    sf::Color color({0, 0, 0, 20});

    rectChoose.setFillColor(color);
    rectChoose.setSize     (rectangle.getSize());
    rectChoose.setPosition (rectangle.getPosition());

    sf::Vector2f cursorPosition = GetCursorPosition(*window);

    if(IsInsideRect(cursorPosition, &rectangle))
    {
        window->draw(rectChoose);
    }
}

//-----------------------------------------------------------------------------

void Button::move(sf::Vector2f position)
{
    setPosition(getPosition() + position);
}

//-----------------------------------------------------------------------------

void Button::setWindow(sf::RenderWindow &window)
{
    this->window = &window;
}

//-----------------------------------------------------------------------------

void Button::setTexture(sf::Texture texture)
{
    buttonTexture = texture;

    rectangle.setTexture(&buttonTexture);
}

//-----------------------------------------------------------------------------

void Button::setTextureRect(sf::IntRect rect)
{
    rectangle.setTextureRect(rect);
}

//-----------------------------------------------------------------------------

void Button::setScale(sf::Vector2f scale)
{
    rectangle.setScale(scale);

    text.setScale(scale);
    setTextPosition();
}

//-----------------------------------------------------------------------------

void Button::setSize(sf::Vector2f size)
{
    rectangle.setSize(size);
}

//-----------------------------------------------------------------------------

void Button::setPosition(sf::Vector2f position)
{
    rectangle.setPosition(position);
    setTextPosition();
}

void Button::setFillColor(sf::Color color)
{
    rectangle.setFillColor(color);
}

//-----------------------------------------------------------------------------

void Button::setTextString(std::string str)
{
    textStr = str;

    text.setString(str);
    text.setScale (rectangle.getScale());

    fontText.loadFromFile("Fonts\\ariblk.ttf");
    text.setFont(fontText);
    text.setCharacterSize(25);

    //text = startText;

    setTextHeight  ();
    setTextLength  (maxLengthText);
    setTextPosition();
}

//-----------------------------------------------------------------------------

void Button::setTextLength(float length)
{
    std::string textStr = text.getString();

    printf("%c\n", textStr[1]);

    sf::FloatRect boundsText = text.getLocalBounds();
    sf::Vector2f  scaleRect  = rectangle.getScale();
    sf::Vector2f  sizeRect   = rectangle.getSize();

    if(length > sizeRect.x)
    {
        length = sizeRect.x;
    }

    if(boundsText.width <= length)
    {
        maxLengthText = boundsText.width;

        return;
    }

    maxLengthText = length;

    std::string newTextStr = "";
    float       nowLength  = 0;

    int lenStr = textStr.length();
    for(int i = 1; i <= lenStr; i++)
    {
        float letterWidth = text.findCharacterPos(i).x - text.findCharacterPos(i - 1).x;
        letterWidth /= scaleRect.x;

        nowLength += letterWidth;

        if(nowLength <= length)
        {
            newTextStr += textStr[i - 1];
        }
        else
        {
            break;
        }
    }

    text.setString(newTextStr);
    setTextPosition();
}

//-----------------------------------------------------------------------------

void Button::setVisible(float visible)
{
    if(visible > 1) visible = 1;
    if(visible < 0) visible = 0;

    sf::Color colorRect = rectangle.getFillColor();
    colorRect.a = 255 * visible;
    rectangle.setFillColor(colorRect);

    sf::Color colorText = text.getColor();
    colorText.a         = 255 * visible;
    text.setColor(colorText);
}

//-----------------------------------------------------------------------------

sf::Vector2f Button::getPosition()
{
    return rectangle.getPosition();
}

//-----------------------------------------------------------------------------

sf::Vector2f Button::getSize()
{
    return rectangle.getSize();
}

//-----------------------------------------------------------------------------

sf::Vector2f Button::getScale()
{
    return rectangle.getScale();
}

/*! @} */

//-----------------------------------------------------------------------------
//}     End of Button
//-----------------------------------------------------------------------------

#endif
