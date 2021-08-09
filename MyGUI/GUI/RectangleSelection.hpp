#ifndef RECTANGLE_SELECTION
#define RECTANGLE_SELECTION

//-----------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <float.h>
#include <vector>
#include "Button.hpp"

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


#endif
