#include "drone.hpp"

void Drone::initialize()
{
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.f, -10.f));
    triangle.setPoint(1, sf::Vector2f(10.f, 10.f));
    triangle.setPoint(2, sf::Vector2f(-10.f, 10.f));
    triangle.setFillColor(sf::Color::Red);

    // Label
    // GUI elements don't need to be drawn, handled by GUI manager
    label = GUI::Manager::getInstance().buildLabel();
    label->setText("Drones: 9");
    label->setTextSize(12);
}

Drone::Drone()
{
    initialize();
}

Drone::Drone(sf::Vector2f pos, float rot, sf::Vector2f scale)
{
    initialize();

    setPosition(pos);
    setRotation(rot);
    setScale(scale);
}

Drone::~Drone()
{
}

void Drone::update(float dt)
{
    triangle.setPosition(getPosition());
    triangle.setRotation(getRotation());
    label->setPosition(getPosition().x + 5, getPosition().y + 5);
}

void Drone::handleInput(sf::Event &event)
{
}

void Drone::render(sf::RenderWindow &window)
{
    // only non-gui elements need to be drawn
    window.draw(triangle);
}
