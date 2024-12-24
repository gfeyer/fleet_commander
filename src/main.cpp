#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

#include "gui.hpp"

int main() {
    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "In-Game Popup Example");
    window.setFramerateLimit(60);

    tgui::Gui gui(window);
    gui.setFont("resources/fonts/toxigenesis.otf");
    // gui.setRelativeView({0,0,0.9f,0.9f});

    // Main Game UI: Background Label
    auto mainLabel = tgui::Label::create("Game Window Running...");
    mainLabel->setPosition({"10%", "10%"});
    mainLabel->setTextSize(24);
    gui.add(mainLabel);

    // Open Popup with Main Button
    auto openPopupButton = tgui::Button::create("Open Popup");
    openPopupButton->setSize({"150px", "50px"});
    openPopupButton->setPosition({"10%", "80%"});
    openPopupButton->onPress([&]() {
        auto popup = GUI::createPopup();
        gui.add(popup);
    });

    gui.add(openPopupButton);

    // World world;

    auto time = sf::Clock();


    // Main Game Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            gui.handleEvent(event); // Pass events to GUI

            // world.handleInput(event);
        }

        // Update(dt)
        // world.update(time.restart().asSeconds());

        // Draw(window)
        window.clear(sf::Color(50, 50, 50));
        // world.render(window);
        gui.draw();

        window.display();
    }

    return 0;
}
