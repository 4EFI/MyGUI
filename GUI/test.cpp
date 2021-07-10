#include "GUI/Slider.hpp"
#include "GUI/CheckBox.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Slider slider;

    //slider.setRectSize({ 350, 3 });

    //CheckBox checkBox(50, 50, 0, 0);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        ControllSliders();

        //checkBox.Check(window);

        window.clear();

        slider.draw(window);

        printf("%f\n", slider.getValue());

        //checkBox.Render(&window);

        window.display();
    }
}
