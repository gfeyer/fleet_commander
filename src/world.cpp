#include "world.hpp"

#include "util/logger.hpp"
#include "factory.hpp"

World::World()
{
    log_info << "Creating World";
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(100, 100), 0, sf::Vector2f(1, 1)));
}

World::~World()
{
    log_info << "Destroying World";
}

void World::update(float dt)
{
    for(auto& entity : entities)
    {
        entity->update(dt);
    }
}

void World::render(sf::RenderWindow &window)
{
    for(auto& entity : entities)
    {
        entity->render(window);
    }
}

void World::handleInput(sf::Event &event)
{
    log_info << "World Input Handled";
    for(auto& entity : entities)
    {
        entity->handleInput(event);
    }
}
