#include "scene.hpp"

#include "util/logger.hpp"
#include "factory.hpp"
#include "resource.hpp"
#include "config.hpp"
#include "outpost.hpp"

Scene::Scene()
{
    log_info << "Creating World";

    // Load background texture
    const sf::Texture& backgroundTexture = Resource::Manager::getInstance().getTexture(Resource::Paths::BACKGROUND_4);

    // Create a sprite for the background
    // TODO: belongs in scene
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background to fit the window
    // sf::Vector2u windowSize = window.getSize();
    sf::Vector2u windowSize = sf::Vector2u(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    // Create Factories
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(rand() % 1000, rand() % 700), 0, sf::Vector2f(1, 1)));
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(rand() % 1000, rand() % 700), 0, sf::Vector2f(1, 1)));
    entities.push_back(std::make_shared<Factory>(sf::Vector2f(rand() % 1000, rand() % 700), 0, sf::Vector2f(1, 1)));

    // Create Outposts
    entities.push_back(std::make_shared<Outpost>(sf::Vector2f(rand() % 1000, rand() % 700), 0, sf::Vector2f(1, 1)));
    entities.push_back(std::make_shared<Outpost>(sf::Vector2f(rand() % 1000, rand() % 700), 0, sf::Vector2f(1, 1)));
    entities.push_back(std::make_shared<Outpost>(sf::Vector2f(rand() % 1000, rand() % 700), 0, sf::Vector2f(1, 1)));


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
    // Render background
    window.draw(this->backgroundSprite);

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
