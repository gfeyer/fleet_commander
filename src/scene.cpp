#include "scene.hpp"

#include "util/logger.hpp"
#include "factory.hpp"

Scene::Scene()
{
    log_info << "Creating World";
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(100, 100), 0, sf::Vector2f(1, 1)));
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(300, 400), 0, sf::Vector2f(1, 1)));
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(600, 250), 0, sf::Vector2f(1, 1)));
}

Scene::~Scene()
{
    log_info << "Destroying World";
}

void Scene::update(float dt)
{
    for(auto& entity : entities)
    {
        entity->update(dt);
    }
}

void Scene::render(sf::RenderWindow &window)
{
    for(auto& entity : entities)
    {
        entity->render(window);
    }
}

void Scene::handleInput(sf::Event &event)
{
    log_info << "World Input Handled";
    for(auto& entity : entities)
    {
        entity->handleInput(event);
    }
}
