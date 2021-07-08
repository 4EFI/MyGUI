#include <SFML/Graphics.hpp>
#include <vector>

class CheckBox;

static std::vector<CheckBox*> checkBoxes;

class CheckBox
{
private:
    float weight;
    float height;

    bool  state = false;
    bool  pr    = false;

    sf::RectangleShape rect;
    sf::RectangleShape box;

    //void Check(sf::RenderWindow &window);

public:
    CheckBox(float weight, float height, int posX, int posY);

    void Check(sf::RenderWindow &window);

    void Render(sf::RenderWindow *window);
	void Loop  (sf::RenderWindow &window);

	bool GetState();
	void SetPosition(float newX, float newY);
};

//-----------------------------------------------------------------------------
//{     CheckBox realization
//-----------------------------------------------------------------------------

void CheckBox::Check(sf::RenderWindow &window)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

    sf::Vector2f pos      = window.mapPixelToCoords(pixelPos);

    pos = window.mapPixelToCoords((sf::Vector2i)pos);

    if (rect.getGlobalBounds().contains(pos.x, pos.y))
    {
        if (!state)
        {
            if (!pr && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                pr = true;
            }

            if  (pr && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                pr = false;
                state = true;
            }
        }

        if (state)
        {
            if (!pr && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                pr = true;
            }

            if (pr && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                pr = false;
                state = false;
            }
        }
    }
}

void CheckBox::SetPosition(float newX, float newY)
{
    rect.setPosition(newX,                 newY);
    box. setPosition(newX + weight * 0.20, newY + height * 0.20);
}

bool CheckBox::GetState()
{
    return state;
}

void CheckBox::Loop(sf::RenderWindow &window)
{
    int size = checkBoxes.size();
    for(int i = 0; i < size; i++)
    {
        checkBoxes[i]->Check(window);
    }
}
void CheckBox::Render(sf::RenderWindow *window)
{
    window->draw(rect);

    if(state)
    {
        window->draw(box);
    }
}

CheckBox::CheckBox(float weight, float height, int posX, int posY)
{
    rect.setFillColor   (sf::Color::White);
    rect.setOutlineColor(sf::Color::Black);
    box. setFillColor   (sf::Color::Black);

    rect.setOutlineThickness(5.f);

    this->weight = weight;
    this->height = height;

    rect.setPosition(posX,                 posY);
    box. setPosition(posX + weight * 0.20, posY + height * 0.20);

    rect.setSize(sf::Vector2f(weight,                 height));
    box. setSize(sf::Vector2f(weight - weight * 0.40, height - height * 0.40));

    checkBoxes.push_back(this);
}

//-----------------------------------------------------------------------------
//}     End of CheckBox
//-----------------------------------------------------------------------------

