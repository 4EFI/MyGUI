#include <SFML/Graphics.hpp>
#include "../MyGUI/GUIController.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Slider slider;

    slider.setPosition({100, 100});
    slider.setIndicatorColor(sf::Color::Red);

    slider.setRange(0, 100);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        GUIControll();

        printf("%f\n", slider.getValue());

        window.clear();

        slider.draw(window);

        window.display();
    }
}
