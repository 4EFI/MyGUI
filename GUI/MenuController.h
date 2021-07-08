#ifndef MENUCONTROLLER
#define MENUCONTROLLER

//-----------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <float.h>
#include <vector>

#define DEFAULT_BUTTON "Textures\\DefaultButton.png"

//-----------------------------------------------------------------------------

sf::Vector2f GetCursorPosition(sf::RenderWindow &window);

bool IsInsideRect(sf::Vector2f cursorPosition, sf::RectangleShape *rectangle);

//-----------------------------------------------------------------------------

class Button
{
protected:
    sf::RectangleShape rectangle;
    sf::Texture        buttonTexture;

    sf::Text           text;

    bool       isLeftButtonPressed = false;

    int        buttonIndex;
    static int countButtons;
    float      maxLengthText = FLT_MAX;

    void SetTextPosition();
    void SetTextHeight();

public:
    Button();

    void Show     (sf::RenderWindow &window);
    bool IsPressed(sf::RenderWindow &window);
    bool IsClicked(sf::RenderWindow &window);

    void SetTexture(const char path[]);

    void SetScale    (sf::Vector2f scale);
    void SetSize     (sf::Vector2f size);
    void SetPosition (sf::Vector2f position);
    void SetFillColor(sf::Color    color);

    int  GetIndex();

    void SetText      (sf::Text *text);
    void SetTextLength(float    length);
};

//-----------------------------------------------------------------------------
//{     Button realization
//-----------------------------------------------------------------------------

int Button::countButtons = 0;

//-----------------------------------------------------------------------------

/*!
\defgroup main_module Main Module
*/

Button::Button()
{
    rectangle.setSize({200, 100});

    countButtons++;
    buttonIndex = countButtons;
}

//-----------------------------------------------------------------------------

void Button::SetTextPosition()
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

void Button::SetTextHeight()
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

            button.Show(window);

            window.display();
        }
    }
\endcode

*/

void Button::Show(sf::RenderWindow &window)
{
    window.draw(rectangle);

    window.draw(text);
}

//-----------------------------------------------------------------------------

/*!

\brief Function shows if the button is pressed

\param window The window where the button press will be read

\return TRUE - the button is pressed else - FALSE

Example using
\code
    Button button;

    if(button.IsPressed(window))
    {
        ...
    }
\endcode

*/

bool Button::IsPressed(sf::RenderWindow &window)
{
    sf::Vector2f cursorPosition = GetCursorPosition(window);
    sf::Vector2f buttonPosition = rectangle.getPosition();
    sf::Vector2f scale          = rectangle.getScale();

    sf::Vector2u sizeButton = { rectangle.getSize().x * scale.x,
                                rectangle.getSize().y * scale.y };

    if(GetAsyncKeyState(VK_LBUTTON))
    {
        isLeftButtonPressed = true;
    }
    else
    {
        isLeftButtonPressed = false;
    }

    if(IsInsideRect(cursorPosition, &rectangle))
    {
        //printf("asdf\n");

        if(isLeftButtonPressed)
        {
            return 1;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

bool Button::IsClicked(sf::RenderWindow &window)
{
    if(!isLeftButtonPressed & IsPressed(window))
    {
        return 1;
    }

    if(!GetAsyncKeyState(VK_LBUTTON))
    {
        isLeftButtonPressed = false;
    }

    return 0;
}

//-----------------------------------------------------------------------------

void Button::SetTexture(const char path[])
{
    buttonTexture.loadFromFile(path);

    sf::Vector2f sizeTexture = (sf::Vector2f)buttonTexture.getSize();

    rectangle.setSize   (sizeTexture);
    rectangle.setTexture(&buttonTexture);
}

//-----------------------------------------------------------------------------

void Button::SetScale(sf::Vector2f scale)
{
    rectangle.setScale(scale);

    text.setScale(scale);
    SetTextPosition();
}

//-----------------------------------------------------------------------------

void Button::SetSize(sf::Vector2f size)
{
    rectangle.setSize(size);
}

//-----------------------------------------------------------------------------

void Button::SetPosition(sf::Vector2f position)
{
    rectangle.setPosition(position);
    SetTextPosition();
}

void Button::SetFillColor(sf::Color color)
{
    rectangle.setFillColor(color);
}

//-----------------------------------------------------------------------------

int Button::GetIndex()
{
    return buttonIndex;
}

//-----------------------------------------------------------------------------

void Button::SetText(sf::Text *text)
{
    this->text = *text;

    this->text.setScale(rectangle.getScale());

    SetTextHeight  ();
    SetTextLength  (maxLengthText);
    SetTextPosition();
}

//-----------------------------------------------------------------------------

void Button::SetTextLength(float length)
{
    std::string textStr = text.getString();

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
    SetTextPosition();
}

/*! @} */

//-----------------------------------------------------------------------------
//}     End of block
//-----------------------------------------------------------------------------

class RectangleSelection : public Button
{
private:
    sf::Vector2f startPosition;

    const int countCircles = 8;
    sf::CircleShape circles[8];

    void MoveCircleCenter(sf::Vector2f position, sf::CircleShape *circle);

    sf::Vector2f GetCircleCentre(sf::CircleShape *circle);
    bool         IsInsideCircle (sf::CircleShape *circle, sf::Vector2f position);

    void ShowEditTools(sf::RenderWindow &window, float scale = 1);

public:
    float radiusEditCircle   = 4;
    float radiusButtonCircle = 15;

    bool showEditTools = false;

    void Show                (sf::RenderWindow &window, float scale = 1, sf::Vector2f centrePos = {0, 0});

    bool SetTextureBoundaries(sf::RenderWindow &window, float scale = 1, sf::Vector2f centrePos = {0, 0});
    void Edit                (sf::RenderWindow &window, float scale = 1, sf::Vector2f centrePos = {0, 0});
};

//-----------------------------------------------------------------------------
//{     RectangleSelection realization
//-----------------------------------------------------------------------------

void RectangleSelection::MoveCircleCenter(sf::Vector2f position, sf::CircleShape *circle)
{
    circle->setPosition(position.x - radiusEditCircle, position.y - radiusEditCircle);
}

//-----------------------------------------------------------------------------

sf::Vector2f RectangleSelection::GetCircleCentre(sf::CircleShape *circle)
{
    sf::Vector2f position = circle->getPosition();
    position.x += radiusEditCircle;
    position.y += radiusEditCircle;

    return position;
}

//-----------------------------------------------------------------------------

bool RectangleSelection::IsInsideCircle(sf::CircleShape *circle, sf::Vector2f position)
{
    sf::Vector2f circleCentre = GetCircleCentre(circle);

    if((position.x - circleCentre.x)*(position.x - circleCentre.x) +
       (position.y - circleCentre.y)*(position.y - circleCentre.y) <= radiusButtonCircle * radiusButtonCircle)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------

void RectangleSelection::Show(sf::RenderWindow &window, float scale, sf::Vector2f centrePos)
{
    rectangle.setScale   (scale, scale);
    rectangle.setPosition(startPosition * scale + centrePos);

    window.draw(rectangle);

    if(showEditTools)
    {
        ShowEditTools(window, scale);
    }
}

//-----------------------------------------------------------------------------

void RectangleSelection::ShowEditTools(sf::RenderWindow &window, float scale)
{
    sf::Vector2f position = rectangle.getPosition();
    sf::Vector2f size     = rectangle.getSize();

    size *= scale;

    for(int i = 0; i < countCircles; i++)
    {
        circles[i].setRadius(radiusEditCircle);
        circles[i].setFillColor(sf::Color(0, 0, 0));
    }

    //Angular circles (L_UP & R_DOWN)
    MoveCircleCenter({ position.x,          position.y },          &circles[0]);
    MoveCircleCenter({ position.x + size.x, position.y + size.y }, &circles[2]);
    //Angular circles (R_UP & L_DOWN)
    MoveCircleCenter({ position.x + size.x, position.y },          &circles[1]);
    MoveCircleCenter({ position.x,          position.y + size.y }, &circles[3]);

    //Middle circles (Left & Right)
    MoveCircleCenter({ position.x,              position.y + size.y / 2 }, &circles[4]);
    MoveCircleCenter({ position.x + size.x,     position.y + size.y / 2 }, &circles[5]);
    //Middle circles (Up & Down)
    MoveCircleCenter({ position.x + size.x / 2, position.y },              &circles[6]);
    MoveCircleCenter({ position.x + size.x / 2, position.y + size.y },     &circles[7]);

    for(int i = 0; i < countCircles; i++)
    {
        circles[i].setRadius(radiusEditCircle);

        window.draw(circles[i]);
    }
}

//-----------------------------------------------------------------------------

bool RectangleSelection::SetTextureBoundaries(sf::RenderWindow &window, float scale, sf::Vector2f centrePos)
{
    bool isSetBoundaries = false;

    static bool leftButtonPressed = false;

    static sf::Vector2f pNow;

    if(GetAsyncKeyState(VK_LBUTTON))
    {
        if(!leftButtonPressed)
        {
            startPosition  = GetCursorPosition(window) - centrePos;
            startPosition /= scale;

            leftButtonPressed = true;
        }

        pNow  = GetCursorPosition(window) - centrePos;
        pNow /= scale;
    }
    else if (!GetAsyncKeyState(VK_LBUTTON) && leftButtonPressed == true)
    {
        leftButtonPressed = false;
        isSetBoundaries   = true;
    }

    rectangle.setSize(pNow - startPosition);

    rectangle.setFillColor(sf::Color(15, 180, 140));

    return isSetBoundaries;
}

//-----------------------------------------------------------------------------

void RectangleSelection::Edit(sf::RenderWindow &window, float scale, sf::Vector2f centrePos)
{
    sf::Vector2f cursorPosition;
    cursorPosition = GetCursorPosition(window);

    static sf::Vector2f sizeRec;

    static bool leftButtonPressed = false;

    static int  numEditCircle     = -1;
    static int  numOppositeCircle = -1;

    if(!GetAsyncKeyState(VK_LBUTTON))
    {
        leftButtonPressed = false;
        numEditCircle     = -1;
        numOppositeCircle = -1;

        return;
    }

    if(GetAsyncKeyState(VK_LBUTTON))
    {
        if(!leftButtonPressed)
        {
            leftButtonPressed = true;

            for(int i = 0; i < countCircles; i++)
            {
                if(IsInsideCircle(&circles[i], cursorPosition))
                {
                    numEditCircle = i;
                    break;
                }
            }

            if(numEditCircle == -1) return;

            if     (numEditCircle >= 0 && numEditCircle <= 3)
            {
                numOppositeCircle = (numEditCircle + 2) % 4;
            }
            else if(numEditCircle == 4 || numEditCircle == 6)
            {
                numOppositeCircle = 2;
            }
            else if(numEditCircle == 5 || numEditCircle == 7)
            {
                numOppositeCircle = 0;
            }

            startPosition = GetCircleCentre(&circles[numOppositeCircle]);
            startPosition = (startPosition - centrePos) / scale;

            sizeRec = rectangle.getSize();
        }
    }

    cursorPosition = (cursorPosition - centrePos) / scale;

    if(leftButtonPressed)
    {
        if     (numEditCircle >= 0 && numEditCircle <= 3)
        {
            rectangle.setSize(cursorPosition - startPosition);
        }
        else if(numEditCircle >= 4 && numEditCircle <= 5)
        {
            int k = (numEditCircle == 4) ? -1 : 1;

            rectangle.setSize({ cursorPosition.x - startPosition.x, k * sizeRec.y });
        }
        else if(numEditCircle >= 6 && numEditCircle <= 7)
        {
            int k = (numEditCircle == 6) ? -1 : 1;

            rectangle.setSize({ k * sizeRec.x, cursorPosition.y - startPosition.y });
        }
    }
}

//-----------------------------------------------------------------------------
//}  End of Block
//-----------------------------------------------------------------------------

sf::Vector2f GetCursorPosition(sf::RenderWindow &window)
{
    sf::Vector2f cursorPosition;

    cursorPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
    cursorPosition = window.mapPixelToCoords((sf::Vector2i)cursorPosition);
}

//-----------------------------------------------------------------------------

bool IsInsideRect(sf::Vector2f cursorPosition, sf::RectangleShape *rectangle)
{
    sf::Vector2f position = rectangle->getPosition();
    sf::Vector2f size     = rectangle->getSize();
    sf::Vector2f scale    = rectangle->getScale();

    size = { size.x * scale.x, size.y * scale.y };

    if(cursorPosition.x >= position.x && cursorPosition.x <= position.x + size.x &&
       cursorPosition.y >= position.y && cursorPosition.y <= position.y + size.y)
    {
        return 1;
    }

    return 0;
}

//-----------------------------------------------------------------------------

#endif
