#include <SFML/Graphics.hpp>
#include "../MyGUI/GUIController.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    CheckBox checkBox;

    checkBox.setCheckBoxSize({70, 70});
    checkBox.setFlagSize    ({40, 40});
    checkBox.setPosition    ({50, 50});

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        GUIControll();

        printf("%d\n", checkBox.getState());

        window.clear();

        checkBox.draw(window);

        window.display();
    }
}

