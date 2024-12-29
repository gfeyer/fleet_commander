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

    // Create Window
    sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Fleet Dominion");
    window.setFramerateLimit(60);

    Scene scene(window);
    auto time = sf::Clock();

    // Game Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                scene.handleInput(event);
            }

            if(event.type == sf::Event::KeyPressed) {
                scene.handleInput(event);
            }
        }

        // Update logic
        scene.update(time.restart().asSeconds());

        // Render window
        window.clear(sf::Color(50, 50, 50));
        scene.render();
        window.display();
    }

    return 0;
}
