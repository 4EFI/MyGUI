#ifndef LABEL
#define LABEL

#include "SFML/Graphics.hpp"
#include <string.h>

class Label
{
private:
    sf::Text text;
    sf::Font font;

public:
    Label(const std::string str = "");

    void draw(sf::RenderWindow &window);

    void setString(const std::string str);
    void setFont  (sf::Font          font);
};

//-----------------------------------------------------------------------------
//{     Label realization
//-----------------------------------------------------------------------------

Label::Label(const std::string str)
{
    font.loadFromFile("arial.ttf");

    text.setString(str);
}

//-----------------------------------------------------------------------------

void Label::draw(sf::RenderWindow &window)
{
    window.draw(text);
}

//-----------------------------------------------------------------------------

void Label::setString(const std::string str)
{
    text.setString(str);
}

//-----------------------------------------------------------------------------

void Label::setFont()

//-----------------------------------------------------------------------------
//}     End of Label
//-----------------------------------------------------------------------------

#endif
