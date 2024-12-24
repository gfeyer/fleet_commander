#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "resource.hpp"

namespace GUI {

    const unsigned int FONT_SIZE = 18;
    
tgui::ChildWindow::Ptr createPopup() {
    auto theme = Resource::Manager::getInstance().getTheme(Resource::Paths::DARK_THEME);
    
    // Create Popup Window (ChildWindow)
    auto popup = tgui::ChildWindow::create("Widgets Popup");
    popup->setRenderer(theme->getRenderer("ChildWindow"));
    popup->setTitleTextSize(FONT_SIZE);
    popup->setTextSize(FONT_SIZE);
    popup->setSize({"400px", "400px"});
    popup->setPosition({"50%", "50%"});
    popup->setOrigin(0.5f, 0.5f);
    popup->setTitleButtons(tgui::ChildWindow::TitleButton::Close);
    popup->setResizable(true);  // Enable resizing for the popup
    // popup->onSizeChange([](tgui::Vector2f newSize) {
    //     std::cout << "Popup resized to: " << newSize.x << "x" << newSize.y << std::endl;
    // });

    // ─── Label ───
    auto label = tgui::Label::create("Welcome to TGUI Widgets!");
    label->setRenderer(theme->getRenderer("Label"));
    label->setPosition({"5%", "5%"});
    label->setTextSize(FONT_SIZE);
    popup->add(label);

    // ─── Button ───
    auto button = tgui::Button::create("Click Me");
    button->setRenderer(theme->getRenderer("Button"));
    button->setTextSize(FONT_SIZE);
    button->setSize({"120px", "30px"});
    button->setPosition({"5%", "15%"});
    button->onPress([]() { std::cout << "Button Pressed!" << std::endl; });
    popup->add(button);

    // ─── Checkbox ───
    auto checkbox = tgui::CheckBox::create("Enable Feature");
    checkbox->setRenderer(theme->getRenderer("CheckBox"));
    checkbox->setPosition({"5%", "25%"});
    checkbox->setTextSize(FONT_SIZE);
    popup->add(checkbox);

    // ─── RadioButton ───
    auto radioButton1 = tgui::RadioButton::create();
    radioButton1->setRenderer(theme->getRenderer("RadioButton"));
    radioButton1->setText("Option 1");
    radioButton1->setPosition({"5%", "35%"});
    radioButton1->setTextSize(FONT_SIZE);
    popup->add(radioButton1);

    auto radioButton2 = tgui::RadioButton::create();
    radioButton2->setRenderer(theme->getRenderer("RadioButton"));
    radioButton2->setText("Option 2");
    radioButton2->setPosition({"5%", "42%"});
    radioButton2->setTextSize(FONT_SIZE);
    popup->add(radioButton2);

    // ─── EditBox ───
    auto editBox = tgui::EditBox::create();
    editBox->setRenderer(theme->getRenderer("EditBox"));
    editBox->setSize({"200px", "30px"});
    editBox->setPosition({"5%", "50%"});
    editBox->setDefaultText("Enter text...");
    editBox->setTextSize(FONT_SIZE);
    popup->add(editBox);

    // ─── Slider ───
    auto slider = tgui::Slider::create();
    slider->setRenderer(theme->getRenderer("Slider"));
    slider->setSize({"200px", "18px"});
    slider->setPosition({"5%", "60%"});
    slider->setValue(50);
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
    comboBox->setTextSize(FONT_SIZE);
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
    listBox->setTextSize(FONT_SIZE);
    popup->add(listBox);

    // ─── SpinButton ───
    auto spinButton = tgui::SpinButton::create();
    spinButton->setRenderer(theme->getRenderer("SpinButton"));
    spinButton->setPosition({"75%", "15%"});
    spinButton->setSize({"50px", "80px"});
    spinButton->setMinimum(0);
    spinButton->setMaximum(10);
    spinButton->setTextSize(FONT_SIZE);
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
    closeButton->setTextSize(FONT_SIZE);
    closeButton->onPress([popup]() {
        std::cout << "Popup Closed!" << std::endl;
        if (popup->getParent()) {
            popup->getParent()->remove(popup);
        }
    });
    popup->add(closeButton);

    return popup;
}

}

#endif // GUI_HPP