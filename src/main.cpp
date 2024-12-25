#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

#include "gui.hpp"
#include "Game/Scene.hpp"
#include "Config.hpp"

#include "Core/Entity.hpp"
int main() {
    // seed srand
    srand(time(NULL));

    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "In-Game Popup Example");
    window.setFramerateLimit(60);

    // GUI initialization
    GUI::ResourceManager::getInstance().initialize(window);

    // Main Game UI: Background Label
    // auto label = GUI::ResourceManager::getInstance().buildLabel();
    // label->setText("Game Window Running...");
    // label->setPosition({"5%", "5%"});
    // label->setTextSize(24);

    // // Open Popup with Main Button
    // auto openPopupButton = GUI::ResourceManager::getInstance().buildButton();
    // openPopupButton->setSize({"150px", "50px"});
    // openPopupButton->setPosition({"10%", "80%"});
    // openPopupButton->onPress([&]() {
    //     auto popup = GUI::ResourceManager::getInstance().buildPopupShowcase();
    // });

    Scene scene;
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
            bool handled = GUI::ResourceManager::getInstance().handleEvent(event);
            
            if(!handled && event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    scene.handleInput(event);
                }
            }
        }

        // Update(dt)
        scene.update(time.restart().asSeconds());

        // Draw(window)
        window.clear(sf::Color(50, 50, 50));
        // window.draw(backgroundSprite); // Draw the background image

        scene.render(window);
        GUI::ResourceManager::getInstance().draw();

        window.display();
    }

    return 0;
}
