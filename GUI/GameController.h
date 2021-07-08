#ifndef GAMECONTROLLER
#define GAMECONTROLLER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>

const int MaxCountTuxtures   = 100;
const int MaxCountSprites    = 100;
const int MaxCountAnimations = 25;

//----------Класс и прототипы--------------------------------------------------------
#if 1

using sf::Texture;
using sf::Image;
using sf::Sprite;

class TextureManager
{
   Texture textures[MaxCountTuxtures];

   bool LoadFromFile(char path[]);
};

struct Animation
{
    Sprite  sprites [MaxCountSprites];
    char    name    [MaxCountAnimations];
    int     countFrames;
    int     stateFrame;
};

class Object2D
{
private:
    Animation animations[15];
    int       countAnimations;

    clock_t lastTime;

    int nowNumberAnim;

    void GetFormat(const char str[], char format[]);
    void DeleteFormatInStr(const char str[], char newStr[]);
    int  GetNumberAnim(const char word[]);

    bool colliderVisible;

public:
    Object2D();

    sf::Vector2f position;
    sf::Vector2f scale;

    float weight;
    float height;

    void SetDefaultSprite(const char path[]);

    void AddAnim(const char path[], const char nameState[], int countFrames, const sf::IntRect collider = {0, 0, 0, 0});

    int  Animate(const char name[], float msBetweenFrames, sf::RenderWindow &window);

    void Move(float x, float y);
    void SetScale(float x, float y);
    void SetPosition(float x, float y);
};

#endif
//---------------Конец---------------------------------------------------------------

//----------Реализация Функций-------------------------------------------------------
#if 1

Object2D::Object2D(): countAnimations(1)
{
    scale = { 1.0, 1.0 };

    for (int i = 0; i < 10; i++)
    {
        strcpy(animations[i].name, "");
    }

    lastTime = 0;
    nowNumberAnim = 0;
}

void Object2D::GetFormat(const char str[], char format[])
{
    int sizeStr = strlen(str);
    bool isFormat = false;
    for (int i = 0, j = 0; i < sizeStr; i++)
    {
        if (str[i] == '.') isFormat = true;

        if (isFormat)
        {
            format[j] = str[i];
            j++;
        }
    }
}

void Object2D::DeleteFormatInStr(const char str[], char newStr[])
{
    int sizeStr = strlen(str);
    for (int i = 0; i < sizeStr; i++)
    {
        if (str[i] == '.') break;

        newStr[i] = str[i];
    }
}

int Object2D::GetNumberAnim(const char word[])
{
    int numberAnimation = -1;
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(word, animations[i].name) == 0)
        {
            numberAnimation = i;
            break;
        }
    }

    return numberAnimation;
}

int Object2D::AddAnim(const char path[], const char nameState[], int countFrames, const sf::IntRect collider)
{
    for (int i = 0; i < countFrames; i++)
    {
        char fullPath[50] = "";
        char format[10] = "";
        char pathNoFormat[50] = "";

        GetFormat(path, format);
        DeleteFormatInStr(path, pathNoFormat);

        strcat(fullPath, pathNoFormat);

        //В конце прибавляем номер анимации начиная с нуля
        int sizePath = strlen(fullPath);
        char num[4] = "";
        itoa(i, num, 10);

        strcat(fullPath, num);

        //В конец приписываем формат файла
        strcat(fullPath, format);

        //Загрузка спрайта
        animations[countAnimations].textures[i].loadFromFile(fullPath);

        if (collider.width != 0 && collider.height != 0)
        {
            animations[countAnimations].sprites[i].setTextureRect(collider);
            animations[countAnimations].sprites[i].setTexture(animations[countAnimations].textures[i]);
        }
        else
        {
            animations[countAnimations].sprites[i].setTexture(animations[countAnimations].textures[i]);
        }

    }

    strcat(animations[countAnimations].name, nameState);

    animations[countAnimations].countFrames = countFrames;
    animations[countAnimations].stateFrame  = 0;

    countAnimations++;

    return countAnimations - 1;
}

int Object2D::Animate(const char name[], float msBetweenFrames, sf::RenderWindow &window)
{
    int nowNumberAnim = GetNumberAnim(name);

    if (nowNumberAnim == -1) return -1;

    clock_t secondsInGame = clock();

    int stateFrame = animations[nowNumberAnim].stateFrame;

    if (stateFrame == animations[nowNumberAnim].countFrames)
    {
        animations[nowNumberAnim].stateFrame = 0;
        stateFrame = 0;
    }

    animations[nowNumberAnim].sprites[stateFrame].setPosition(position);
    animations[nowNumberAnim].sprites[stateFrame].setScale(scale);

    if (secondsInGame - lastTime >= msBetweenFrames)
    {
        lastTime = clock();

        animations[nowNumberAnim].stateFrame++;
    }

    window.draw(animations[nowNumberAnim].sprites[stateFrame]);

    return stateFrame;
}

void Object2D::Move(float x, float y)
{
    position = { x, y };

    animations[nowNumberAnim].sprites[animations[nowNumberAnim].stateFrame].setPosition(position);
}

void Object2D::SetScale(float x, float y)
{
    scale = { x, y };

    animations[nowNumberAnim].sprites[animations[nowNumberAnim].stateFrame].setScale(scale);
}

void Object2D::SetPosition(float x, float y)
{
    position = { x, y };

    animations[nowNumberAnim].sprites[animations[nowNumberAnim].stateFrame].setPosition(position);
}

void Object2D::SetDefaultSprite(const char path[])
{
    animations[0].textures[0].loadFromFile(path);
    animations[0].sprites[0].setTexture(animations[0].textures[0]);

    strcat(animations[0].name, "default");
    animations[0].countFrames = 1;
    animations[0].stateFrame = 0;
}

#endif
//---------------Конец---------------------------------------------------------------

#endif
