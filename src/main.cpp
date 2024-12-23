#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>


int main() {
    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "In-Game Popup Example");
    tgui::Gui gui(window);

    // 🌟 Main Game UI: Background Label
    auto mainLabel = tgui::Label::create("Game Window Running...");
    mainLabel->setPosition({"10%", "10%"});
    mainLabel->setTextSize(24);
    gui.add(mainLabel);

    // 🌟 Create Popup Window (ChildWindow)
    auto popup = tgui::ChildWindow::create("Popup Menu");
    popup->setSize({"300px", "200px"});
    popup->setPosition({"50%", "50%"});
    popup->setOrigin(0.5f, 0.5f);
    popup->setTitleButtons(tgui::ChildWindow::TitleButton::Close);
    popup->onClose([&]() {
        gui.remove(popup); // Remove popup when closed
    });

    // 🌟 Add Text to Popup
    auto popupLabel = tgui::Label::create("This is a popup menu!");
    popupLabel->setPosition({"10%", "20%"});
    popupLabel->setTextSize(18);
    popup->add(popupLabel);

    // 🌟 Add Button to Popup
    auto closeButton = tgui::Button::create("Ok");
    closeButton->setSize({"100px", "40px"});
    closeButton->setPosition({"50%", "80%"});
    closeButton->setOrigin(0.5f, 0.5f);
    closeButton->onPress([&]() {
        std::cout<< "pressed ok" << std::endl;
        gui.remove(popup); // Remove popup when button is clicked
    });
    popup->add(closeButton);

    // 🌟 Open Popup with Main Button
    auto openPopupButton = tgui::Button::create("Open Popup");
    openPopupButton->setSize({"150px", "50px"});
    openPopupButton->setPosition({"10%", "80%"});
    openPopupButton->onPress([&]() {
        gui.add(popup); // Show the popup
    });
    gui.add(openPopupButton);

    // 🎮 Main Game Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            gui.handleEvent(event); // Pass events to GUI
        }

        window.clear(sf::Color(50, 50, 50));
        gui.draw();
        window.display();
    }

    return 0;
}
