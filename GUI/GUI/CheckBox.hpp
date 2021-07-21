#ifndef CHECKBOX
#define CHECKBOX

#include "SFML/Graphics.hpp"
#include "Button.hpp"
#include <vector>

//-----------------------------------------------------------------------------

void ControllCheckBoxes();

//-----------------------------------------------------------------------------

class CheckBox
{
private:
    sf::RenderWindow *window = 0;

    bool state = false;

    Button             checkbox;
    sf::RectangleShape flag;

    void setFlagMiddle();

public:
    CheckBox(float weight = 50, float height = 50, int posX = 0, int posY = 0);

    void check();
    void draw (sf::RenderWindow &window);

	void setFlagSize       (sf::Vector2f   size);
	void setCheckBoxSize   (sf::Vector2f   size);
	void setPosition       (sf::Vector2f   position);
	void setScale          (sf::Vector2f   scale);
	void setFlagTexture    (sf::Texture   &texture);
	void setCheckBoxTexture(sf::Texture   &texture);
    void setFlagRect       (sf::IntRect  rect);
    void setCheckBoxRect   (sf::IntRect  rect);
    void setState          (bool         state);

    bool getState();
};

//-----------------------------------------------------------------------------

static std::vector<CheckBox*> checkBoxes;

//-----------------------------------------------------------------------------
//{     CheckBox realization
//-----------------------------------------------------------------------------

void CheckBox::setFlagMiddle()
{
    sf::Vector2f scale        = flag.getScale();

    sf::Vector2f sizeCheckBox = checkbox.getSize();
    sf::Vector2f sizeFlag     = flag.    getSize();

    sf::Vector2f posCheckBox = checkbox.getPosition();
    sf::Vector2f pos;

    pos.x = posCheckBox.x + (sizeCheckBox - sizeFlag).x / 2 * scale.x;
    pos.y = posCheckBox.y + (sizeCheckBox - sizeFlag).y / 2 * scale.y;

    flag.setPosition(pos);
}

//-----------------------------------------------------------------------------

CheckBox::CheckBox(float weight, float height, int posX, int posY)
{
    checkbox.setFillColor(sf::Color::White);
    flag. setFillColor   (sf::Color::Black);

    checkbox.setSize({ weight,                 height });
    flag.    setSize({ weight - weight * 0.40, height - height * 0.40 });

    setFlagMiddle();

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
        window.draw(flag);
    }
}

//-----------------------------------------------------------------------------

void CheckBox::setPosition(sf::Vector2f newPos)
{
    checkbox.setPosition(newPos);

    setFlagMiddle();
}

//-----------------------------------------------------------------------------

void CheckBox::setFlagSize(sf::Vector2f size)
{
	sf::Vector2f sizeCheckBox = checkbox.getSize();

    if(size.x > sizeCheckBox.x) size.x = sizeCheckBox.x;
    if(size.y > sizeCheckBox.y) size.y = sizeCheckBox.y;

	flag.setSize(size);

	setFlagMiddle();
}

//-----------------------------------------------------------------------------

void CheckBox::setCheckBoxSize(sf::Vector2f size)
{
	sf::Vector2f sizeFlag = flag.getSize();

	if(size.x < sizeFlag.x) size.x = sizeFlag.x;
	if(size.y < sizeFlag.y) size.y = sizeFlag.y;

	checkbox.setSize(size);

	setFlagMiddle();
}

//-----------------------------------------------------------------------------

void CheckBox::setScale(sf::Vector2f scale)
{
    checkbox.setScale(scale);
    flag.    setScale(scale);

    setFlagMiddle();
}

//-----------------------------------------------------------------------------

void CheckBox::setFlagTexture(sf::Texture &texture)
{
	flag.setTexture(&texture);
}

//-----------------------------------------------------------------------------

void CheckBox::setCheckBoxTexture(sf::Texture &texture)
{
    checkbox.setTexture(texture);
}

//-----------------------------------------------------------------------------

void CheckBox::setFlagRect(sf::IntRect rect)
{
    flag.setTextureRect(rect);
}

//-----------------------------------------------------------------------------

void CheckBox::setCheckBoxRect(sf::IntRect rect)
{
    checkbox.setTextureRect(rect);
}

//-----------------------------------------------------------------------------

void CheckBox::setState(bool state)
{
    this->state = state;
}

//-----------------------------------------------------------------------------

bool CheckBox::getState()
{
    return state;
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

#endif
