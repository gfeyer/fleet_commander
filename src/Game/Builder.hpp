#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <unordered_map>
#include <string>

#include "Core/Entity.hpp"

#include "Components/DroneComponent.hpp"
#include "Components/ShieldComponent.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/PowerPlantComponent.hpp"
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

#include "Utils/Random.hpp"

namespace Game {

    EntityID createFactory(GameEntityManager& entityManager, std::string name = "", sf::Vector2f position = sf::Vector2f(0.f, 0.f), Components::Faction faction = Components::Faction::NEUTRAL, float productionRate = 1.f, float shieldRegenRate = 1.f) {
        // Create Factory

        EntityID factoryID = entityManager.createEntity();

        entityManager.addComponent(factoryID, Components::FactoryComponent{name, productionRate});
        entityManager.addComponent(factoryID, Components::TransformComponent{position, 0, sf::Vector2f(1, 1)});
        auto shape = sf::RectangleShape({Config::FACTORY_SIZE, Config::FACTORY_SIZE});
        sf::Color color{100,100,100};
        shape.setFillColor(color);
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
        entityManager.addComponent(factoryID, Components::ShapeComponent{std::make_shared<sf::RectangleShape>(shape)});
        entityManager.addComponent(factoryID, Components::LabelComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::FACTORY_SIZE+5, - float(Config::FACTORY_SIZE))
        });
        entityManager.addComponent(factoryID, Components::HoverComponent{});
        entityManager.addComponent(factoryID, Components::SelectableComponent{});
        entityManager.addComponent(factoryID, Components::FactionComponent{faction});
        entityManager.addComponent(factoryID, Components::GarissonComponent{});
        entityManager.addComponent(factoryID, Components::ShieldComponent{0, 10, shieldRegenRate});
        return factoryID;
    }

    EntityID createPowerPlant(GameEntityManager& entityManager, std::string name = "", sf::Vector2f position = sf::Vector2f(0.f, 0.f), Components::Faction faction = Components::Faction::NEUTRAL, float shieldRegenRate = 1.f, unsigned int energyCapacity=10) {
        EntityID powerPlantID = entityManager.createEntity();
        entityManager.addComponent(powerPlantID, Components::PowerPlantComponent{name,energyCapacity});
        entityManager.addComponent(powerPlantID, Components::TransformComponent{position, 0, sf::Vector2f(1, 1)});
        auto shape = sf::CircleShape(Config::POWER_PLANT_RADIUS);
        sf::Color color{100,100,100};
        shape.setFillColor(color);
        shape.setOrigin(Config::POWER_PLANT_RADIUS, Config::POWER_PLANT_RADIUS);
        entityManager.addComponent(powerPlantID, Components::ShapeComponent{std::make_shared<sf::CircleShape>(shape)});
        entityManager.addComponent(powerPlantID, Components::LabelComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::POWER_PLANT_RADIUS*2, -2*float(Config::POWER_PLANT_RADIUS))
        });
        entityManager.addComponent(powerPlantID, Components::HoverComponent{});
        entityManager.addComponent(powerPlantID, Components::SelectableComponent{});
        entityManager.addComponent(powerPlantID, Components::FactionComponent{faction});
        entityManager.addComponent(powerPlantID, Components::GarissonComponent{});

        float maxShield = energyCapacity;
        entityManager.addComponent(powerPlantID, Components::ShieldComponent{0, maxShield, shieldRegenRate});
        return powerPlantID;
    }

    EntityID createDrone(GameEntityManager& entityManager, std::string name = "", Components::Faction faction = Components::Faction::NEUTRAL) {
        EntityID droneID = entityManager.createEntity();
        
        entityManager.addComponent(droneID, Components::DroneComponent{name});
        entityManager.addComponent(droneID, Components::TransformComponent{sf::Vector2f(0.f,0.f), 0.f, sf::Vector2f(1, 1)});
        auto shape = std::make_shared<sf::ConvexShape>();
        shape->setPointCount(3);
        shape->setOrigin(sf::Vector2f(0.f, 0.f));
        shape->setPoint(0, sf::Vector2f(0.f, -Config::DRONE_LENGTH));  // Top point
        shape->setPoint(1, sf::Vector2f(-Config::DRONE_LENGTH, Config::DRONE_LENGTH)); // Bottom-left point
        shape->setPoint(2, sf::Vector2f(Config::DRONE_LENGTH, Config::DRONE_LENGTH));  // Bottom-right point
        sf::Color color{100,100,100};
        shape->setFillColor(color);
        entityManager.addComponent(droneID, Components::ShapeComponent{shape});
        entityManager.addComponent(droneID, Components::LabelComponent{name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::DRONE_LENGTH*2, 5)
        });

        entityManager.addComponent(droneID, Components::MoveComponent{100.f, 0.f});
        entityManager.addComponent(droneID, Components::FactionComponent{faction});

        return droneID;
    }
}


#endif // BUILDER_HPP