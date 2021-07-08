#include "MenuController.h"
#include "Slider.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Slider slider;
    slider.SetWindow(&window);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        MoveIndicators();

        window.clear();

        slider.Show();

        window.display();
    }
}
