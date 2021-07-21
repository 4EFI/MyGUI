#ifndef BUTTONS_LIST
#define BUTTONS_LIST

#include "Button.hpp"
#include <vector>

class ButtonsList
{
private:
    sf::RenderWindow *window = 0;

    int countButtons = 1;
    std::vector<Button> buttons;

    Button             mainButton;

    sf::RectangleShape openTriangle;
    sf::Texture        openTriangleTexture;

    float visible = 0;

    bool isOpened            = false;
    bool isVisible           = false;
    int  selectedButtonIndex = 0;

    sf::Vector2f position = {0, 0};

    void setStartPosition();
    void setOpenTrianglePosition();

public:
    ButtonsList();

    void moveButtons();

    void draw  (sf::RenderWindow &window);
    void open  ();
    void select();

    void setDefault     (int          choise);
    void setCountButtons(int          countButtons);
    void setPosition    (sf::Vector2f position);

    Button *getButton(int numberButton);
};

std::vector<Button*> buttonsLists;

//----------------------------------------------------------------------------
//{       ButtonsList realization
//----------------------------------------------------------------------------

void ButtonsList::setStartPosition()
{
    float allSize = mainButton.getSize().y;

    for(int i = 0; i < countButtons; i++)
    {
        buttons[i].setPosition({ position.x, position.y + allSize });

        allSize += buttons[i].getSize().y;
    }
}

//-----------------------------------------------------------------------------

void ButtonsList::setOpenTrianglePosition()
{
    sf::Vector2f sizeTriangle = openTriangle.getSize();
    sf::Vector2f sizeButton   = mainButton.  getSize();

    openTriangle.setPosition({ position.x + sizeButton.x * 0.83,
                               position.y + (sizeButton.y - sizeTriangle.y) / 2 });
}

//-----------------------------------------------------------------------------

ButtonsList::ButtonsList()
{
    buttons.resize(countButtons);

    openTriangle.setSize({25, 16});

    openTriangleTexture.loadFromFile("Textures\\ButtonsList\\OpenTriangle.png");
    openTriangleTexture.setSmooth(true);

    openTriangle.setTexture(&openTriangleTexture);

    setStartPosition();
}

//-----------------------------------------------------------------------------

void ButtonsList::moveButtons()
{
    if(isOpened)
    {
        visible += 0.005;

        if(visible > 1) visible = 1;
    }
    else
    {
        visible -= 0.008;

        if(visible < 0) visible = 0;
    }

    for(int i = 0; i < countButtons; i++)
    {
        buttons[i].setVisible(visible);
    }
}

//-----------------------------------------------------------------------------

void ButtonsList::draw(sf::RenderWindow &window)
{
    this->window = &window;

    moveButtons();

    for(int i = countButtons - 1; i >= 0; i--)
    {
        buttons[i].draw(window);
    }

    mainButton.draw(window);

    window.draw(openTriangle);
}

//-----------------------------------------------------------------------------

void ButtonsList::open()
{
    if(mainButton.isClicked())
    {
        int k = (isOpened + 1) % 2;

        isOpened = k;
    }
}

//-----------------------------------------------------------------------------

void ButtonsList::select()
{
    if(!isOpened) return;

    for(int i = 0; i < countButtons; i++)
    {
        if(buttons[i].isClicked())
        {
            selectedButtonIndex = i;
            isOpened            = false;

            break;
        }
    }
}

//-----------------------------------------------------------------------------

void ButtonsList::setDefault(int choise)
{
    sf::Texture mainTexture;
    mainTexture.loadFromFile("Textures\\ButtonsList\\MainButton.png");

    mainButton.setTexture(mainTexture);
    mainButton.setSize   ({322.5, 77.5});

    //mainButton.setTextString("123");

    for(int i = 0; i < countButtons; i++)
    {
        sf::Texture texture;
        texture.loadFromFile("Textures\\ButtonsList\\Button.png");

        buttons[i].setTexture(texture);
        buttons[i].setSize   ({322.5, 77.5});

        buttons[i].setTextString("test");
    }

    setOpenTrianglePosition();
    setStartPosition();
}

//-----------------------------------------------------------------------------

void ButtonsList::setCountButtons(int countButtons)
{
    this->countButtons = countButtons;
    buttons.resize(countButtons);

    setStartPosition();
    setOpenTrianglePosition();
}

//-----------------------------------------------------------------------------

void ButtonsList::setPosition(sf::Vector2f position)
{
    this->position = position;

    mainButton.setPosition(position);

    setStartPosition();
    setOpenTrianglePosition();
}

//-----------------------------------------------------------------------------

Button * ButtonsList::getButton(int numberButton)
{
    if(countButtons <= numberButton) return 0;

    return &buttons[numberButton];
}

//----------------------------------------------------------------------------
//}      End of block ButtonsList
//----------------------------------------------------------------------------

void ControllButtonsLists()
{

}

#endif
