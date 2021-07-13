#include <SFML/Graphics.hpp>
#include "Button.hpp"
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

    Button             rect;
    sf::RectangleShape box;

public:
    CheckBox(float weight = 50, float height = 50, int posX = 0, int posY = 0);

    void check();
    void draw (sf::RenderWindow &window);

	void setPosition(sf::Vector2f newPos);

	bool getState();
};

//-----------------------------------------------------------------------------

static std::vector<CheckBox*> checkBoxes;

//-----------------------------------------------------------------------------
//{     CheckBox realization
//-----------------------------------------------------------------------------

CheckBox::CheckBox(float weight, float height, int posX, int posY)
{
    rect.setFillColor   (sf::Color::White);
    //rect.setOutlineColor(sf::Color::Black);
    box. setFillColor   (sf::Color::Black);

    //rect.setOutlineThickness(5.f);

    this->weight = weight;
    this->height = height;

    rect.setPosition({ posX,                 posY });
    box. setPosition({ posX + weight * 0.20, posY + height * 0.20 });

    rect.setSize({ weight,                 height});
    box. setSize({ weight - weight * 0.40, height - height * 0.40 });

    checkBoxes.push_back(this);
}

//-----------------------------------------------------------------------------

void CheckBox::check()
{
    if(window == NULL) return;

    if(rect.isClicked())
    {
        int newState = state + 1;

        state = newState % 2;
    }
}

//-----------------------------------------------------------------------------

void CheckBox::draw(sf::RenderWindow &window)
{
    this->window = &window;
    rect.setWindow(window);

    rect.draw(window);

    if(state)
    {
        window.draw(box);
    }
}

//-----------------------------------------------------------------------------

void CheckBox::setPosition(sf::Vector2f newPos)
{
    rect.setPosition(newPos);
    box. setPosition({ newPos.x + weight * 0.20, newPos.y + height * 0.20 });
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
