#include "GUIController.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Test");

    Slider slider;

    CheckBox checkBox;
    checkBox.setCheckBoxSize({10, 10});

    checkBox.setPosition({100, 100});

    checkBox.setScale({2, 2});

    slider.setPosition({100, 100});

    Button button;

    //button.setTexture(DEFAULT_BUTTON);

    sf::Font font;
    font.loadFromFile("Fonts\\ariblk.ttf");

    sf::Text text("Settings", font, 25);
    text.setColor(sf::Color::Black);

    //button.setVisible(0.3);

    button.setTextString("123");

    ButtonsList buttonsList;
    buttonsList.setCountButtons(3);

    buttonsList.setPosition({100, 100});
    buttonsList.setDefault(0);

    //buttonsList.getButton(0)->setText(text);
    text.setString("123");
    //buttonsList.getButton(1)->setText(text);

    while(true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        GUIControll();
        buttonsList.open();
        buttonsList.select();

        window.clear();

        //slider.draw(window);

        button.draw(window);

        //printf("%f\n", slider.getValue());

        //checkBox.draw(window);

        buttonsList.draw(window);

        window.display();
    }
}
