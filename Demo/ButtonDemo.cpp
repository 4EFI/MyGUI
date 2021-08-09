#include <SFML/Graphics.hpp>
#include "../MyGUI/GUIController.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Button button;

    button.setSize    ({200, 80});
    button.setPosition({100, 100});

    sf::Font font;
    font.loadFromFile("..\\Fonts\\ariblk.ttf");

    sf::Text text("click", font, 25);
    text.setColor(sf::Color::Black);

    button.setText(text);
    button.setTextPosition(middle, middle);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        GUIControll();

        if(button.isClicked())
        {
            printf("click\n");
        }

        window.clear();

        button.draw(window);

        window.display();
    }
}
