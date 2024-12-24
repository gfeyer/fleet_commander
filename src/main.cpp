#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

#include "gui.hpp"
#include "scene.hpp"

int main() {
    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "In-Game Popup Example");
    window.setFramerateLimit(60);

    // Load background texture
    const sf::Texture& backgroundTexture = Resource::Manager::getInstance().getTexture(Resource::Paths::BACKGROUND_4);

    // Create a sprite for the background
    // TODO: belongs in scene
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background to fit the window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    // GUI initialization
    GUI::Manager::getInstance().initialize(window);

    // Main Game UI: Background Label
    auto mainLabel = tgui::Label::create("Game Window Running...");
    mainLabel->setPosition({"10%", "10%"});
    mainLabel->setTextSize(24);
    GUI::Manager::getInstance().add(mainLabel);

    // Open Popup with Main Button
    auto openPopupButton = tgui::Button::create("Open Popup");
    openPopupButton->setSize({"150px", "50px"});
    openPopupButton->setPosition({"10%", "80%"});
    openPopupButton->onPress([&]() {
        auto popup = GUI::createPopup();
        GUI::Manager::getInstance().add(popup);
    });

    GUI::Manager::getInstance().add(openPopupButton);

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
            bool handled = GUI::Manager::getInstance().handleEvent(event);
            
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
        GUI::Manager::getInstance().draw();

        window.display();
    }

    return 0;
}
