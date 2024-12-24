#include "factory.hpp"

#include "util/logger.hpp"
#include "resource.hpp"

Factory::Factory(sf::Vector2f pos, float rot, sf::Vector2f scale) : Entity(pos, rot, scale)
{
    log_info << "Creating Factory";
    sf::RectangleShape rect({50,50});

    // Set shape properties
    rect.setFillColor(sf::Color::Cyan);
    rect.setPosition(position);
    setShape(std::make_unique<sf::RectangleShape>(rect));
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
