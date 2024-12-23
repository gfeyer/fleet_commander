#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

// Function to create and show a popup window
void createPopup(tgui::Gui& gui, const std::string& title, const std::vector<std::string>& inputLabels) {
    // Create a modal ChildWindow
    auto popup = tgui::ChildWindow::create();
    popup->setTitle(title);
    popup->setSize({400, 300}); // Use floats for size
    popup->setPosition({"50%", "50%"}); // Center on screen
    popup->setOrigin(0.5f, 0.5f); // Set origin to center
    popup->setResizable(false);
    popup->setTitleButtons(tgui::ChildWindow::TitleButton::Close);

    // Capture `gui` by reference in the lambda
    popup->onClose([&gui, popup]() mutable {
        gui.remove(popup); // Properly remove the popup
    });

    // Dynamic layout for input fields and labels
    float yOffset = 40;
    std::vector<std::shared_ptr<tgui::EditBox>> inputBoxes;
    for (const auto& label : inputLabels) {
        auto lbl = tgui::Label::create(label);
        lbl->setPosition({10, yOffset});
        lbl->setTextSize(16);
        popup->add(lbl);

        auto inputBox = tgui::EditBox::create();
        inputBox->setPosition({150, yOffset});
        inputBox->setSize({200, 30});
        popup->add(inputBox);
        inputBoxes.push_back(inputBox);

        yOffset += 50;
    }

    // Add a Submit button
    auto submitButton = tgui::Button::create("Submit");
    submitButton->setSize({100, 40});
    submitButton->setPosition({150, yOffset + 10});
    submitButton->onPress([=, &gui]() mutable {
        std::cout << "Popup Inputs:\n";
        for (size_t i = 0; i < inputBoxes.size(); ++i) {
            std::cout << inputLabels[i] << ": " << inputBoxes[i]->getText().toStdString() << "\n";
        }
        gui.remove(popup); // Properly remove the popup after submission
    });
    popup->add(submitButton);

    // Add the popup to the GUI
    gui.add(popup);
}

int main() {
    // Main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML with TGUI Popups");
    tgui::Gui gui(window);

    // Background content (for context)
    // auto mainLabel = tgui::Label::create("Main Window");
    // mainLabel->setPosition({10, 10});
    // mainLabel->setTextSize(24);
    // gui.add(mainLabel);

    // auto openPopup1 = tgui::Button::create("Open Login Popup");
    // openPopup1->setPosition({10, 50});
    // openPopup1->setSize({200, 40});
    // openPopup1->onPress([&]() {
    //     createPopup(gui, "Login", {"Username", "Password"});
    // });
    // gui.add(openPopup1);

    // auto openPopup2 = tgui::Button::create("Open Feedback Popup");
    // openPopup2->setPosition({10, 100});
    // openPopup2->setSize({200, 40});
    // openPopup2->onPress([&]() {
    //     createPopup(gui, "Feedback", {"Name", "Email", "Comments"});
    // });
    // gui.add(openPopup2);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event); // Pass events to TGUI
        }

        window.clear(sf::Color::Black);
        gui.draw();
        window.display();
    }

    return 0;
}
