#include "factory.hpp"

#include "util/logger.hpp"
#include "resource.hpp"
#include "gui.hpp"

Factory::Factory(sf::Vector2f pos, float rot, sf::Vector2f scale) : Entity()
{
    log_info << "Creating Factory";

    setPosition(pos);

    // Shape
    rectangleShape = sf::RectangleShape({50,50});
    rectangleShape.setFillColor(sf::Color::Cyan);

    // Label
    // GUI elements don't need to be drawn, handled by GUI manager
    label = GUI::Manager::getInstance().buildLabel();
    label->setText("Factory #23");
    label->setTextSize(18);
}

Factory::~Factory()
{
    log_info << "Destroying Factory";
}

void Factory::update(float dt)
{
    rectangleShape.setPosition(getPosition());
    label->setPosition(getPosition().x + rectangleShape.getSize().x, getPosition().y + 5);

}

void Factory::handleInput(sf::Event &event)
{
}

void Factory::render(sf::RenderWindow &window)
{
    window.draw(rectangleShape);
}
