#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "Resources/ResourceManager.hpp"
#include <memory>
#include <iostream>

namespace GUI {

const unsigned int FONT_SIZE = 18;

class Manager{
private:
    sf::RenderWindow* window;   // Managed external to the class
    std::unique_ptr<tgui::Gui> gui;
    tgui::Theme::Ptr theme;
    
public:
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    
    void initialize(sf::RenderWindow& window);

    static Manager& getInstance();

    void add(tgui::Widget::Ptr widget);

    void draw();

    bool handleEvent(const sf::Event& event);

    tgui::Label::Ptr buildLabel();

    tgui::Button::Ptr buildButton();

    tgui::ChildWindow::Ptr buildPopup();

    tgui::ChildWindow::Ptr buildPopupShowcase();


private:
    Manager() = default;
    ~Manager() = default;
};

}

#endif // GUI_HPP