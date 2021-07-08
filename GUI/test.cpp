#include "GUI/MenuController.h"
#include "GUI/Slider.h"
#include "GUI/CheckBox.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Slider slider;
    slider.SetWindow(&window);

    CheckBox checkBox(50, 50, 0, 0);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        MoveIndicators();

        checkBox.Check(window);

        window.clear();

        //slider.Show();

        checkBox.Render(&window);

        window.display();
    }
}
