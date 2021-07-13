#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

//-----------------------------------------------------------------------------

void ControllCheckBoxes();

//-----------------------------------------------------------------------------

class CheckBox
{
private:
    sf::RenderWindow *window = 0;

    float weight;
    float height;

    bool  state = false;

    Button             checkbox;
    sf::RectangleShape flag;

public:
    CheckBox(float weight = 50, float height = 50, int posX = 0, int posY = 0);

    void check();
    void draw (sf::RenderWindow &window);
	void setFlagSize(sf::Vector2f newSize);
	void setCheckBoxSize(sf::Vector2f newSize);
	void setPosition(sf::Vector2f newPos);
	void setScale(sf::Vector2f size);
	void setFlagTexture(sf::Texture *texture);
	void setCheckBoxTexture(sf::Texture *texture);
    void setFlagRect(sf::Rect rect);
    void setCheckBoxRect(sf::Rect rect);

    bool getState();
};

//-----------------------------------------------------------------------------

static std::vector<CheckBox*> checkBoxes;
//-----------------------------------------------------------------------------
//{     CheckBox realization
//-----------------------------------------------------------------------------

CheckBox::CheckBox(float weight, float height, int posX, int posY)
{
    checkbox.setFillColor   (sf::Color::White);
    //rect.setOutlineColor(sf::Color::Black);
    flag. setFillColor   (sf::Color::Black);

    //rect.setOutlineThickness(5.f);

    this->weight = weight;
    this->height = height;

    checkbox.setPosition({ posX,                 posY });
    flag. setPosition({ posX + weight * 0.20, posY + height * 0.20 });

    checkbox.setSize({weight, height});
    flag. setSize({ weight - weight * 0.40, height - height * 0.40 });

    checkBoxes.push_back(this);
}

//-----------------------------------------------------------------------------

void CheckBox::check()
{
    if(window == NULL) return;

    if(checkbox.isClicked())
    {
        int newState = state + 1;

        state = newState % 2;
    }
}

//-----------------------------------------------------------------------------

void CheckBox::draw(sf::RenderWindow &window)
{
    this->window = &window;
    checkbox.setWindow(window);

    checkbox.draw(window);

    if(state)
    {
        window.draw(box);
    }
}

//-----------------------------------------------------------------------------

void CheckBox::setPosition(sf::Vector2f newPos)
{
    checkbox.setPosition(newPos);
    flag. setPosition({ newPos.x + weight * 0.20, newPos.y + height * 0.20 });
}

//-----------------------------------------------------------------------------

bool CheckBox::getState()
{
    return state;
}

//-----------------------------------------------------------------------------

void CheckBox::setFlagSize(sf::Vector2f newSize)
{
	flag.setSize(newSize);
}

//-----------------------------------------------------------------------------

void CheckBox::setCheckBoxSize(sf::Vector2f newSize)
{
	checkbox.setSize(newSize);
}

//-----------------------------------------------------------------------------

void CheckBox::setScale(sf::Vector2f size)
{
    checkbox.setScale(size);
    flag.setSize(size);
}

//-----------------------------------------------------------------------------

void CheckBox::setFlagTexture(sf::Texture *texture)
{
	flag.setTexture(texture);
}

//-----------------------------------------------------------------------------

void CheckBox::setCheckBoxTexture(sf::Texture *texture)
{
    checkbox.setTexture(texture);
}

//-----------------------------------------------------------------------------

void CheckBox::setFlagRect(sf::Rect rect)
{
    flag.setTextureRect(rect);
}

//-----------------------------------------------------------------------------

void CheckBox::setCheckBoxRect(sf::Rect rect)
{
    checkbox.setTextureRect(rect);
}

//-----------------------------------------------------------------------------
//}     End of CheckBox
//-----------------------------------------------------------------------------

void ControllCheckBoxes()
{
    int size = checkBoxes.size();
    for(int i = 0; i < size; i++)
    {
        checkBoxes[i]->check();
    }
}

//-----------------------------------------------------------------------------
