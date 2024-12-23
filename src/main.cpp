#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>

tgui::ChildWindow::Ptr createPopup() {
    tgui::Theme::Ptr theme = tgui::Theme::create("resources/Dark.txt");

    // Create Popup Window (ChildWindow)
    auto popup = tgui::ChildWindow::create("Widget Showcase");
    popup->setRenderer(theme->getRenderer("ChildWindow"));
    popup->setSize({"350px", "350px"});
    popup->setPosition({"50%", "50%"});
    popup->setOrigin(0.5f, 0.5f);
    popup->setTitleButtons(tgui::ChildWindow::TitleButton::Close);
    popup->setResizable(true);  // Enable resizing for the popup
    popup->onSizeChange([](tgui::Vector2f newSize) {
        std::cout << "Popup resized to: " << newSize.x << "x" << newSize.y << std::endl;
    });

    // ─── Label ───
    auto label = tgui::Label::create("Welcome to TGUI Widgets!");
    label->setRenderer(theme->getRenderer("Label"));
    label->setPosition({"5%", "5%"});
    label->setTextSize(16);
    popup->add(label);

    // ─── Button ───
    auto button = tgui::Button::create("Click Me");
    button->setRenderer(theme->getRenderer("Button"));
    button->setSize({"120px", "30px"});
    button->setPosition({"5%", "15%"});
    button->onPress([]() { std::cout << "Button Pressed!" << std::endl; });
    popup->add(button);

    // ─── Checkbox ───
    auto checkbox = tgui::CheckBox::create("Enable Feature");
    checkbox->setRenderer(theme->getRenderer("CheckBox"));
    checkbox->setPosition({"5%", "25%"});
    popup->add(checkbox);

    // ─── RadioButton ───
    auto radioButton1 = tgui::RadioButton::create();
    radioButton1->setRenderer(theme->getRenderer("RadioButton"));
    radioButton1->setPosition({"5%", "35%"});
    popup->add(radioButton1);

    auto radioButton2 = tgui::RadioButton::create();
    radioButton2->setRenderer(theme->getRenderer("RadioButton"));
    radioButton2->setPosition({"5%", "42%"});
    popup->add(radioButton2);

    // ─── EditBox ───
    auto editBox = tgui::EditBox::create();
    editBox->setRenderer(theme->getRenderer("EditBox"));
    editBox->setSize({"200px", "30px"});
    editBox->setPosition({"5%", "50%"});
    editBox->setDefaultText("Enter text...");
    popup->add(editBox);

    // ─── Slider ───
    auto slider = tgui::Slider::create();
    slider->setRenderer(theme->getRenderer("Slider"));
    slider->setSize({"200px", "18px"});
    slider->setPosition({"5%", "60%"});
    slider->setMinimum(0);
    slider->setMaximum(100);
    popup->add(slider);

    // ─── ProgressBar ───
    auto progressBar = tgui::ProgressBar::create();
    progressBar->setRenderer(theme->getRenderer("ProgressBar"));
    progressBar->setSize({"200px", "20px"});
    progressBar->setPosition({"5%", "68%"});
    progressBar->setValue(50);
    popup->add(progressBar);

    // ─── ComboBox ───
    auto comboBox = tgui::ComboBox::create();
    comboBox->setRenderer(theme->getRenderer("ComboBox"));
    comboBox->setSize({"200px", "30px"});
    comboBox->setPosition({"5%", "75%"});
    comboBox->addItem("Item 1");
    comboBox->addItem("Item 2");
    comboBox->addItem("Item 3");
    popup->add(comboBox);

    // ─── ListBox ───
    auto listBox = tgui::ListBox::create();
    listBox->setRenderer(theme->getRenderer("ListBox"));
    listBox->setSize({"200px", "60px"});
    listBox->setPosition({"5%", "85%"});
    listBox->addItem("List Item 1");
    listBox->addItem("List Item 2");
    popup->add(listBox);

    // ─── SpinButton ───
    auto spinButton = tgui::SpinButton::create();
    spinButton->setRenderer(theme->getRenderer("SpinButton"));
    spinButton->setPosition({"75%", "15%"});
    spinButton->setSize({"50px", "80px"});
    spinButton->setMinimum(0);
    spinButton->setMaximum(10);
    popup->add(spinButton);

    // ─── Scrollbar ───
    auto scrollbar = tgui::Scrollbar::create();
    scrollbar->setRenderer(theme->getRenderer("Scrollbar"));
    scrollbar->setSize({"20px", "100px"});
    scrollbar->setPosition({"90%", "5%"});
    scrollbar->setMaximum(100);
    scrollbar->setValue(50);
    popup->add(scrollbar);

    // ─── Picture ───
    // auto picture = tgui::Picture::create("resources/sample_image.png");
    // picture->setSize({"80px", "80px"});
    // picture->setPosition({"75%", "50%"});
    // popup->add(picture);

    // ─── Close Button ───
    auto closeButton = tgui::Button::create("Close");
    closeButton->setRenderer(theme->getRenderer("Button"));
    closeButton->setSize({"100px", "30px"});
    closeButton->setPosition({"95%", "95%"});
    closeButton->setOrigin(0.9f, 0.9f);
    closeButton->onPress([popup]() {
        std::cout << "Popup Closed!" << std::endl;
        if (popup->getParent()) {
            popup->getParent()->remove(popup);
        }
    });
    popup->add(closeButton);

    return popup;
}

int main() {
    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "In-Game Popup Example");
    tgui::Gui gui(window);

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
        auto popup = createPopup();
        gui.add(popup);
    });

    gui.add(openPopupButton);

    // Main Game Loop
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
