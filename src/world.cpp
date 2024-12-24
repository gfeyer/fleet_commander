#include "world.hpp"

#include "util/logger.hpp"
World::World()
{
    log_info << "World Created";
}

World::~World()
{
    log_info << "World Destroyed";
}

void World::update(float dt)
{

}

void World::render(sf::RenderWindow &window)
{
}

void World::handleInput(sf::Event &event)
{
    log_info << "World Input Handled";
    
}
