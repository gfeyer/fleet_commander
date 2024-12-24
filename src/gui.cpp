#include "gui.hpp"

namespace GUI {
  void Manager::initialize(sf::RenderWindow& window) {
        this->window = &window;
        gui = std::make_unique<tgui::Gui>(window);

        gui->setFont("resources/fonts/toxigenesis.otf"); // todo: move this to resource manager
        gui->setOpacity(0.8f);

        // Initialize Theme
        this->theme = Resource::Manager::getInstance().getTheme(Resource::Paths::DARK_THEME);
    }

    Manager& Manager::getInstance() {
        static Manager instance; // Singleton instance but allocate once on stack instead of heap, thread-safe
        return instance;
    }

    void Manager::add(tgui::Widget::Ptr widget) {
        gui->add(widget);
    }

    void Manager::draw() {
        gui->draw();
    }

    bool Manager::handleEvent(const sf::Event& event) {
        return gui->handleEvent(event);
    }

    tgui::Label::Ptr Manager::buildLabel(){
        auto label = tgui::Label::create("Hello World!");
        label->setRenderer(theme->getRenderer("Label"));
        label->setTextSize(FONT_SIZE);
        add(label);
        return label;
    }

    tgui::Button::Ptr Manager::buildButton(){
        auto button = tgui::Button::create("Click Me");
        button->setRenderer(theme->getRenderer("Button"));
        button->setTextSize(FONT_SIZE);
        add(button);
        return button;
    }

    tgui::ChildWindow::Ptr Manager::buildPopup(){
        auto popup = tgui::ChildWindow::create("Popup");
        popup->setRenderer(theme->getRenderer("ChildWindow"));
        popup->setTitleTextSize(FONT_SIZE);
        popup->setTextSize(FONT_SIZE);
        popup->setTitleButtons(tgui::ChildWindow::TitleButton::Close);
        add(popup);
        return popup;
    }


}


