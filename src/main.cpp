#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Styled TGUI");
    tgui::Gui gui(window);

    // Load theme
    auto theme = tgui::Theme::create("resources/theme.txt");

    // Create Button
    auto button = tgui::Button::create();
    button->setRenderer(theme->getRenderer("Button"));
    button->setText("Click Me");
    button->setSize({200, 50});
    button->setPosition({50, 50});
    gui.add(button);

    // Create EditBox
    auto editBox = tgui::EditBox::create();
    editBox->setRenderer(theme->getRenderer("EditBox"));
    editBox->setSize({200, 30});
    editBox->setPosition({50, 120});
    gui.add(editBox);

    // Create Label
    auto label = tgui::Label::create("Hello, Styled TGUI!");
    label->setRenderer(theme->getRenderer("Label"));
    label->setPosition({50, 170});
    gui.add(label);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}