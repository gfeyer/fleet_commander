#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <unordered_map>
#include <string>

#include "Core/Entity.hpp"

#include "Components/DroneComponent.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/OutpostComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/TextComponent.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/MoveComponent.hpp"

#include "Utils/Logger.hpp"
#include "Resources/ResourceManager.hpp"

#include "Config.hpp"

namespace Builder {

    Entity createFactory(std::string name = "") {
        // Create Factories
        Entity factory; 
        int i = 1;
        factory.addComponent(Components::FactoryComponent{name});
        factory.addComponent(Components::TransformComponent{sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), 0, sf::Vector2f(1, 1)});
        auto shape = sf::RectangleShape({Config::FACTORY_SIZE, Config::FACTORY_SIZE});
        shape.setFillColor(sf::Color::Cyan);
        factory.addComponent(Components::ShapeComponent{std::make_shared<sf::RectangleShape>(shape)});
        factory.addComponent(Components::TextComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::FACTORY_SIZE+5, 5)
        });
        factory.addComponent(Components::HoverComponent{});
        return factory;
    }

    Entity createOutpost(std::string name = "") {
        Entity outpost;
        outpost.addComponent(Components::OutpostComponent{name});
        outpost.addComponent(Components::TransformComponent{sf::Vector2f(rand() % Config::SCREEN_WIDTH - Config::OUTPOST_RADIUS, rand() % Config::SCREEN_HEIGHT-Config::OUTPOST_RADIUS), 0, sf::Vector2f(1, 1)});
        auto shape = sf::CircleShape(Config::OUTPOST_RADIUS);
        shape.setFillColor(sf::Color::Green);
        outpost.addComponent(Components::ShapeComponent{std::make_shared<sf::CircleShape>(shape)});
        outpost.addComponent(Components::TextComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::OUTPOST_RADIUS*2, 5)
        });
        return outpost;
    }

    Entity createDrone(std::string name = "") {
        Entity drone;
        drone.addComponent(Components::DroneComponent{name});
        drone.addComponent(Components::TransformComponent{sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), float(rand() % 360), sf::Vector2f(1, 1)});
        auto shape = std::make_shared<sf::ConvexShape>();
        shape->setPointCount(3);
        shape->setOrigin(sf::Vector2f(0.f, 0.f));
        shape->setPoint(0, sf::Vector2f(0.f, -Config::DRONE_LENGTH));  // Top point
        shape->setPoint(1, sf::Vector2f(-Config::DRONE_LENGTH, Config::DRONE_LENGTH)); // Bottom-left point
        shape->setPoint(2, sf::Vector2f(Config::DRONE_LENGTH, Config::DRONE_LENGTH));  // Bottom-right point

        shape->setFillColor(sf::Color::Red);
        drone.addComponent(Components::ShapeComponent{shape});
        drone.addComponent(Components::TextComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::DRONE_LENGTH*2, 5)
        });

        drone.addComponent(Components::MoveComponent{100.f, 0.f});

        return drone;
    }
}


#endif // BUILDER_HPP