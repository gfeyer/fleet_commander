#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

// Global flag for dragging UI panel
bool isDragging = false;
sf::Vector2f dragOffset;

int main() {
    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game with TGUI UI");
    tgui::Gui gui(window);

    // -----------------
    // Game Content
    // -----------------
    sf::CircleShape player(30);
    player.setFillColor(sf::Color::Green);
    player.setPosition(400, 300);

    // -----------------
    // UI Panel (Movable)
    // -----------------
    auto panel = tgui::Panel::create({"300px", "200px"});
    panel->setPosition({"200px", "150px"});
    panel->getRenderer()->setBackgroundColor(sf::Color(50, 50, 50, 200));
    gui.add(panel);

    // Label inside the panel
    auto label = tgui::Label::create("Game Controls");
    label->setTextSize(18);
    label->setPosition({"10px", "10px"});
    panel->add(label);

    // Button inside the panel
    auto button = tgui::Button::create("Click Me");
    button->setSize({"100px", "40px"});
    button->setPosition({"10px", "50px"});
    button->onPress([]() {
        std::cout << "Button Clicked!" << std::endl;
    });
    panel->add(button);

    // Text Box inside the panel
    auto textBox = tgui::EditBox::create();
    textBox->setSize({"200px", "30px"});
    textBox->setPosition({"10px", "110px"});
    textBox->setDefaultText("Type something...");
    panel->add(textBox);

    // -----------------
    // Main Loop
    // -----------------
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle Mouse Events for Dragging the Panel
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                    if (panel->isMouseOnWidget(mousePos)) {
                        isDragging = true;
                        // dragOffset = mousePos - panel->getPosition();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                }
            }

            if (event.type == sf::Event::MouseMoved && isDragging) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
                panel->setPosition({mousePos.x - dragOffset.x, mousePos.y - dragOffset.y});
            }

            // Pass events to TGUI
            gui.handleEvent(event);
        }

        // -----------------
        // Rendering
        // -----------------
        window.clear(sf::Color::Black);

        // Draw Game Content
        window.draw(player); 

        // Draw GUI
        gui.draw();

        window.display();
    }

    return 0;
}
