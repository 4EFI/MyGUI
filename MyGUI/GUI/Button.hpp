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

enum PositionState
{
    left,
    middle,
    right,
    down,
    top,
    no_changes
};

//-----------------------------------------------------------------------------

class Button
{
protected:
    sf::RectangleShape rectangle;
    sf::Texture        buttonTexture;

    sf::RectangleShape rectChoose;

    sf ::Text startText;
    sf ::Text text;

    sf::Vector2f localTextPosition = {0, 0};

    bool isLeftButtonPressed = false;
    bool isInsideRect        = true;

    sf::RenderWindow *window = 0;

    float maxLengthText = FLT_MAX;

    void setTextHeight();

public:
    Button();

    void draw     (sf::RenderWindow &window);
    bool isPressed();
    bool isClicked();

    void isCursorInsideBox();
    bool isHovered();

    void move           (sf ::Vector2f      position);
    void setTexture     (sf ::Texture       texture);
    void setTextureRect (sf ::IntRect       rect);
    void setWindow      (sf ::RenderWindow &window);
    void setScale       (sf ::Vector2f      scale);
    void setSize        (sf ::Vector2f      size);
    void setPosition    (sf ::Vector2f      position);
    void setFillColor   (sf ::Color         color);
    void setText        (sf ::Text          text);
    void setTextString  (std::string        str);
    void setTextPosition(sf ::Vector2f      localPosition);
    void setTextPosition(PositionState      posX, PositionState posY);
    void setTextLength  (float              length);
    void setVisible     (float              visible);

    sf::Vector2f getPosition();
    sf::Vector2f getSize    ();
    sf::Vector2f getScale   ();
    sf::Vector2f getTextPosition();
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
}

//-----------------------------------------------------------------------------

void Button::setTextHeight()
{
    if(text.getString() == "") return;

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
localTextPosition
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

bool Button::isHovered()
{
    if(window == NULL) return 0;

    sf::Vector2f cursorPosition = GetCursorPosition(*window);

    if(IsInsideRect(cursorPosition, &rectangle))
    {
        return 1;
    }

    return 0;
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

    text.setScale   (scale);
    text.setPosition(getPosition() + localTextPosition);
}

//-----------------------------------------------------------------------------

void Button::setSize(sf::Vector2f size)
{
    rectangle.setSize(size);

    if(text.getString() != "")
    {
        setTextHeight();
        setTextLength(maxLengthText);

        this->text.setPosition(getPosition() + localTextPosition);
    }
}

//-----------------------------------------------------------------------------

void Button::setPosition(sf::Vector2f position)
{
    rectangle.setPosition(position);

    if(text.getString() != "")
    {
        text.setPosition(position + localTextPosition);
    }
}

void Button::setFillColor(sf::Color color)
{
    rectangle.setFillColor(color);
}

//-----------------------------------------------------------------------------

void Button::setText(sf::Text text)
{
    startText = text;

    this->text = text;

    setTextHeight();
    setTextLength(maxLengthText);

    this->text.setPosition(getPosition() + localTextPosition);
    this->text.setScale(getScale());
}

//-----------------------------------------------------------------------------

void Button::setTextString(std::string str)
{
    text.setString(str);
    text.setScale (rectangle.getScale());

    setTextHeight   ();
    setTextLength   (maxLengthText);
    text.setPosition(getPosition() + localTextPosition);
}

void Button::setTextPosition(sf::Vector2f localPosition)
{
    if(text.getString() == "") return;

    sf::Vector2f positionRect = rectangle.getPosition();
    sf::Vector2f scaleRect    = rectangle.getScale();
    sf::Vector2f sizeRect     = rectangle.getSize();

    sizeRect = { sizeRect.x * scaleRect.x, sizeRect.y * scaleRect.y };

    sf::FloatRect textBounds = text.getLocalBounds();

    textBounds.width  *= scaleRect.x;
    textBounds.height *= scaleRect.y;
    textBounds.left   *= scaleRect.x;
    textBounds.top    *= scaleRect.y;

    float maxLengthText = sizeRect.x - localPosition.x;
    if(textBounds.width > maxLengthText)
    {
        setTextLength(maxLengthText);
    }

    text.setPosition(getPosition() + localPosition);

    localTextPosition = localPosition;
}

//-----------------------------------------------------------------------------

void Button::setTextPosition(PositionState posX, PositionState posY)
{
    if(text.getString() == "") return;

    sf::Vector2f positionRect = rectangle.getPosition();
    sf::Vector2f scaleRect    = rectangle.getScale();
    sf::Vector2f sizeRect     = rectangle.getSize();

    sizeRect = { sizeRect.x * scaleRect.x, sizeRect.y * scaleRect.y };

    sf::FloatRect textBounds = text.getLocalBounds();

    textBounds.width  *= scaleRect.x;
    textBounds.height *= scaleRect.y;
    textBounds.left   *= scaleRect.x;
    textBounds.top    *= scaleRect.y;

    switch(posX)
    {
    case left:
        localTextPosition.x = 0;
        break;

    case middle:
        localTextPosition.x = (sizeRect.x - textBounds.width) / 2 - textBounds.left;
        break;

    case right:
        localTextPosition.x = sizeRect.x - textBounds.width - textBounds.left;
        break;
    }

    switch(posY)
    {
    case top:
        localTextPosition.y = 0;
        break;

    case middle:
        localTextPosition.y = (sizeRect.y - textBounds.height) / 2 - textBounds.top;
        break;

    case down:
        localTextPosition.y = sizeRect.y - textBounds.height - textBounds.top;
        break;
    }

    text.setPosition(getPosition() + localTextPosition);
}

//-----------------------------------------------------------------------------

void Button::setTextLength(float length)
{
    if(text.getString() == "") return;

    std::string textStr = startText.getString();

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
