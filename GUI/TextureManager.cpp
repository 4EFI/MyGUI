#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "MenuController.h"

const float MinScale = 0.15;

//-----------------------------------------------------------------------------

void SetCentrePosition(sf::Vector2f *centrePos, float v_move);

void SetScale(float *scale, float v_scaling, float dt);

void ShowMenuPanel(sf::RenderWindow &window);

//-----------------------------------------------------------------------------

int main()
{
    char pathToTexture[100] = "Textures\\SpriteSheet.png";

    sf::Texture texture;
    texture.loadFromFile(pathToTexture);

    sf::Sprite spriteImg(texture);

    sf::RenderWindow window(sf::VideoMode(1000, 700), "Texture Manager");

    float scale = 1;
    sf::Vector2f centrePos = {0, 0};

    float v_moveCentre = 0.5;
    float v_scaling    = 0.001;

    sf::Clock clock;

    RectangleSelection rectangle;
    bool isSetBoundaries = false;

    sf::Texture backGroundTexture;
    backGroundTexture.loadFromFile("Textures\\ClearBackGround.jpg");

    sf::Sprite backGroundSprite(backGroundTexture);
    backGroundSprite.setScale(0.65, 0.65);

    sf::Font font;
    font.loadFromFile("Fonts\\arial.ttf");

    sf::Text text("Click!", font, 40);

    Button button;
    button.SetScale  ({0.7, 0.7});
    button.SetTexture(DEFAULT_BUTTON);
    button.SetPosition({100, 20});

    button.SetText(&text);
    button.SetTextLength(100);

    while(true)
    {
        bool canClick = true;

        float dt = clock.getElapsedTime().asMicroseconds();
		dt /= 1000;
		clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        SetCentrePosition(&centrePos, v_moveCentre);
        SetScale         (&scale,     v_scaling, dt);

        window.clear({255, 255, 255});

        window.draw(backGroundSprite);

        if(!isSetBoundaries)
        {
            isSetBoundaries = rectangle.SetTextureBoundaries(window, scale, centrePos);

            rectangle.showEditTools = false;
        }
        else
        {
            rectangle.showEditTools = true;
            rectangle.Edit(window, scale, centrePos);
        }

        rectangle.Show(window, scale, centrePos);

        spriteImg.setPosition(centrePos);
        spriteImg.setScale   (scale, scale);

        window.draw(spriteImg);

        ShowMenuPanel(window);
        button.Show  (window);

        if(button.IsClicked(window) && canClick)
        {
            printf("Click11!!!\n");
            canClick = false;
        }

        if(rectangle.IsClicked(window) && canClick)
        {
            printf("Click!!!\n");
            canClick = false;
        }

        window.display();

        canClick = true;
    }
}

//-----------------------------------------------------------------------------

void SetCentrePosition(sf::Vector2f *centrePos, float v_move)
{
    static bool rightButtonPressed = false;

    static POINT pStart;
    static POINT pNow;

    if(GetAsyncKeyState(VK_RBUTTON))
    {
        if(!rightButtonPressed)
        {
            GetCursorPos(&pStart);

            rightButtonPressed = true;
        }

        GetCursorPos(&pNow);

        if(pStart.x - pNow.x != 0 || pStart.y - pNow.y != 0)
        {
            centrePos->x -= (pStart.x - pNow.x) * v_move;
            centrePos->y -= (pStart.y - pNow.y) * v_move;

            GetCursorPos(&pStart);
        }
    }
    else
    {
        rightButtonPressed = false;
    }
}

//-----------------------------------------------------------------------------

void SetScale(float *scale, float v_scaling, float dt)
{
    if     (GetAsyncKeyState(VK_UP))
    {
        (*scale) += v_scaling * dt;
    }
    else if(GetAsyncKeyState(VK_DOWN))
    {
        (*scale) -= v_scaling * dt;
    }

    if(*scale < MinScale)
    {
        (*scale) = MinScale;
    }
}

//-----------------------------------------------------------------------------

void ShowMenuPanel(sf::RenderWindow &window)
{
    sf::RectangleShape panel;

    sf::Vector2u sizeWindow = window.getSize();

    panel.setSize({ sizeWindow.x, 80 });
    panel.setFillColor(sf::Color(220, 220, 220));

    window.draw(panel);
}

//-----------------------------------------------------------------------------
