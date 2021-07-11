#include "GUI/Slider.hpp"
#include "GUI/CheckBox.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Slider slider;

    CheckBox checkBox(50, 50, 0, 0);

    slider.setPosition({100, 100});
    //slider.setScale   ({2, 2});

    Button button;

    button.setTexture(DEFAULT_BUTTON);

    sf::Font font;
    font.loadFromFile("Fonts\\ariblk.ttf");

    sf::Text text("Settings", font, 25);

    button.setText(&text);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        ControllSliders();
        ControllCheckBoxes();

        window.clear();

        //if(button.isPressed())
        //{
            //slider.draw(window);
        //}

        //button.draw(window);

        //printf("%f\n", slider.getValue());

        checkBox.draw(window);

        window.display();
    }
}
