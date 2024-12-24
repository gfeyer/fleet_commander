#include "factory.hpp"

#include "util/logger.hpp"
#include "resource.hpp"
#include "gui.hpp"

Factory::Factory(sf::Vector2f pos, float rot, sf::Vector2f scale) : Entity(pos, rot, scale)
{
    log_info << "Creating Factory";

    // Shape
    rectangleShape = sf::RectangleShape({50,50});
    rectangleShape.setFillColor(sf::Color::Cyan);
    rectangleShape.setPosition(position);

    // Label
    label = GUI::Manager::getInstance().buildLabel();
    label->setText("Factory #23");
    label->setPosition(rectangleShape.getPosition().x + rectangleShape.getSize().x, rectangleShape.getPosition().y + 5);
    label->setTextSize(18);
}

Factory::~Factory()
{
    log_info << "Destroying Factory";
}

void Factory::update(float dt)
{
}

void Factory::handleInput(sf::Event &event)
{
}

void Factory::render(sf::RenderWindow &window)
{
    window.draw(rectangleShape);
}
