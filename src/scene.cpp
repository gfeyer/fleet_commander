#include "scene.hpp"

#include "util/logger.hpp"
#include "factory.hpp"
#include "resource.hpp"
#include "config.hpp"
#include "outpost.hpp"
#include "config.hpp"
#include "drone.hpp"
#include "components.hpp"
#include "entity.hpp"


Scene::Scene()
{
    log_info << "Creating Scene";

    // // Load background texture
    // const sf::Texture& backgroundTexture = Resource::Manager::getInstance().getTexture(Resource::Paths::BACKGROUND_4);

    // // Create a sprite for the background
    // sf::Sprite backgroundSprite;
    // backgroundSprite.setTexture(backgroundTexture);

    // // Scale the background to fit the window
    // // sf::Vector2u windowSize = window.getSize();
    // sf::Vector2u windowSize = sf::Vector2u(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    // sf::Vector2u textureSize = backgroundTexture.getSize();
    // backgroundSprite.setScale(
    //     static_cast<float>(windowSize.x) / textureSize.x,
    //     static_cast<float>(windowSize.y) / textureSize.y
    // );

    Entity background;
    auto texture = Resource::Manager::getInstance().getTexture(Resource::Paths::BACKGROUND_4);
    background.addComponent(SpriteComponent{texture});
    sf::Vector2u windowSize = sf::Vector2u(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    sf::Vector2u textureSize = texture.getSize();
    background.addComponent(
        TransformComponent{
            sf::Vector2f(0,0), 
            0, 
            sf::Vector2f(windowSize.x / textureSize.x, windowSize.y / textureSize.y)
        }
    );


    // Create Factories
    // entities_old.push_back(std::make_shared<Factory>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)));
    // entities_old.push_back(std::make_shared<Factory>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)));
    // entities_old.push_back(std::make_shared<Factory>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)));

    // // Create Outposts
    // entities_old.push_back(std::make_shared<Outpost>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)));
    // entities_old.push_back(std::make_shared<Outpost>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)));
    // entities_old.push_back(std::make_shared<Outpost>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)));

    // // Create Drones
    // entities_old.push_back(std::make_shared<Drone>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), rand() % 360, sf::Vector2f(1, 1)));
    // entities_old.push_back(std::make_shared<Drone>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), rand() % 360, sf::Vector2f(1, 1)));
    // entities_old.push_back(std::make_shared<Drone>(sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), rand() % 360, sf::Vector2f(1, 1)));

}

Scene::~Scene()
{
    log_info << "Destroying Scene";
}

void Scene::update(float dt)
{
    // for(auto& entity : entities_old)
    // {
    //     entity->update(dt);
    // }
}

void Scene::render(sf::RenderWindow &window)
{
    // Render background
    // window.draw(this->backgroundSprite);

    // for(auto& entity : entities_old)
    // {
    //     entity->render(window);
    // }
}

void Scene::handleInput(sf::Event &event)
{
    log_info << "World Input Handled";
    // for(auto& entity : entities_old)
    // {
    //     entity->handleInput(event);
    // }
}
