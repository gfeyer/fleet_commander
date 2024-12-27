#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <unordered_map>
#include <string>

#include "Core/Entity.hpp"

#include "Components/DroneComponent.hpp"
#include "Components/ShieldComponent.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/OutpostComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/GarissonComponent.hpp"
#include "Utils/Logger.hpp"
#include "Resources/ResourceManager.hpp"
#include "Config.hpp"

#include "Game/GameEntityManager.hpp"

namespace Game {

    EntityID createFactory(GameEntityManager& entityManager, std::string name = "", unsigned int factionID = 0, float productionRate = 1.f, float shieldRegenRate = 1.f) {
        log_info << "Creating Factory, " << productionRate << " seconds for every drone";
        // Create Factory

        EntityID factoryID = entityManager.createEntity();

        entityManager.addComponent(factoryID, Components::FactoryComponent{name, productionRate});

        sf::Vector2f position = sf::Vector2f(
            Config::FACTORY_SIZE + rand() % (Config::MAP_WIDTH - 2*Config::FACTORY_SIZE), 
            Config::FACTORY_SIZE + rand() % (Config::MAP_HEIGHT - 2*Config::FACTORY_SIZE)
        );
        entityManager.addComponent(factoryID, Components::TransformComponent{position, 0, sf::Vector2f(1, 1)});
        auto shape = sf::RectangleShape({Config::FACTORY_SIZE, Config::FACTORY_SIZE});
        shape.setFillColor(sf::Color::Color(100, 100, 100));
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
        entityManager.addComponent(factoryID, Components::ShapeComponent{std::make_shared<sf::RectangleShape>(shape)});
        entityManager.addComponent(factoryID, Components::LabelComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::FACTORY_SIZE+5, 5)
        });
        entityManager.addComponent(factoryID, Components::HoverComponent{});
        entityManager.addComponent(factoryID, Components::SelectableComponent{});
        entityManager.addComponent(factoryID, Components::FactionComponent{factionID});
        entityManager.addComponent(factoryID, Components::GarissonComponent{});
        entityManager.addComponent(factoryID, Components::ShieldComponent{0, 10, shieldRegenRate});
        return factoryID;
    }

    EntityID createOutpost(GameEntityManager& entityManager, std::string name = "", unsigned int factionID = 0, float shieldRegenRate = 1.f) {
        
        EntityID outpostID = entityManager.createEntity();
        entityManager.addComponent(outpostID, Components::OutpostComponent{name});
        sf::Vector2f position = sf::Vector2f(
            Config::OUTPOST_RADIUS + rand() % (Config::MAP_WIDTH - 2*Config::OUTPOST_RADIUS), 
            Config::OUTPOST_RADIUS + rand() % (Config::MAP_HEIGHT - 2*Config::OUTPOST_RADIUS)
        );
        entityManager.addComponent(outpostID, Components::TransformComponent{position, 0, sf::Vector2f(1, 1)});
        auto shape = sf::CircleShape(Config::OUTPOST_RADIUS);
        shape.setFillColor(sf::Color::Color(100, 100, 100));
        shape.setOrigin(Config::OUTPOST_RADIUS, Config::OUTPOST_RADIUS);
        entityManager.addComponent(outpostID, Components::ShapeComponent{std::make_shared<sf::CircleShape>(shape)});
        entityManager.addComponent(outpostID, Components::LabelComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::OUTPOST_RADIUS*2, 5)
        });
        entityManager.addComponent(outpostID, Components::HoverComponent{});
        entityManager.addComponent(outpostID, Components::SelectableComponent{});
        entityManager.addComponent(outpostID, Components::FactionComponent{factionID});
        entityManager.addComponent(outpostID, Components::GarissonComponent{});
        entityManager.addComponent(outpostID, Components::ShieldComponent{0, 10, shieldRegenRate});
        return outpostID;
    }

    EntityID createDrone(GameEntityManager& entityManager, std::string name = "", unsigned int factionID = 0) {
        EntityID droneID = entityManager.createEntity();
        
        entityManager.addComponent(droneID, Components::DroneComponent{name});
        entityManager.addComponent(droneID, Components::TransformComponent{sf::Vector2f(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT), float(rand() % 360), sf::Vector2f(1, 1)});
        auto shape = std::make_shared<sf::ConvexShape>();
        shape->setPointCount(3);
        shape->setOrigin(sf::Vector2f(0.f, 0.f));
        shape->setPoint(0, sf::Vector2f(0.f, -Config::DRONE_LENGTH));  // Top point
        shape->setPoint(1, sf::Vector2f(-Config::DRONE_LENGTH, Config::DRONE_LENGTH)); // Bottom-left point
        shape->setPoint(2, sf::Vector2f(Config::DRONE_LENGTH, Config::DRONE_LENGTH));  // Bottom-right point

        shape->setFillColor(sf::Color::Color(100, 100, 100));
        entityManager.addComponent(droneID, Components::ShapeComponent{shape});
        entityManager.addComponent(droneID, Components::LabelComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::DRONE_LENGTH*2, 5)
        });

        entityManager.addComponent(droneID, Components::MoveComponent{100.f, 0.f});
        entityManager.addComponent(droneID, Components::FactionComponent{factionID});

        return droneID;
    }
}


#endif // BUILDER_HPP