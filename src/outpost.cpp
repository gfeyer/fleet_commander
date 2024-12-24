#include "outpost.hpp"

#include "util/logger.hpp"

#include "gui.hpp"
#include "config.hpp"

void Outpost::initialize()
{
    circleShape = sf::CircleShape(Config::OUTPOST_RADIUS);
    circleShape.setFillColor(sf::Color::Green);

    // Label
    // GUI elements don't need to be drawn, handled by GUI manager
    label = GUI::Manager::getInstance().buildLabel();
    label->setText("Outpost #14");
    label->setTextSize(18);
}

Outpost::Outpost()
{
    initialize();
    log_info << "Creating outpost";
}

Outpost::Outpost(sf::Vector2f pos, float rot, sf::Vector2f scale)
{
    initialize();

    log_info << "Creating outpost at " << pos.x << ", " << pos.y;

    setPosition(pos);
    setRotation(rot);
    setScale(scale);
}

Outpost::~Outpost()
{
    log_info << "Destroying outpost";
}

void Outpost::update(float dt)
{
    circleShape.setPosition(getPosition());
    label->setPosition(getPosition().x + circleShape.getRadius(), getPosition().y + 5);
}

void Outpost::handleInput(sf::Event &event)
{
}

void Outpost::render(sf::RenderWindow &window)
{
    window.draw(circleShape);
}
