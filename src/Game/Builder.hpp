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

        entityManager.addComponent<Components::FactoryComponent>(factoryID, name, productionRate);
        entityManager.addComponent<Components::TransformComponent>(factoryID, position, 0, sf::Vector2f(1, 1));
        auto shape = sf::RectangleShape({Config::FACTORY_SIZE, Config::FACTORY_SIZE});
        sf::Color color{100,100,100};
        shape.setFillColor(color);
        shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
        entityManager.addComponent<Components::ShapeComponent>(factoryID, std::make_shared<sf::RectangleShape>(shape));
        entityManager.addComponent<Components::LabelComponent>(factoryID, name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::FACTORY_SIZE+5, - float(Config::FACTORY_SIZE))
        );
        entityManager.addComponent<Components::HoverComponent>(factoryID);
        entityManager.addComponent<Components::SelectableComponent>(factoryID);
        entityManager.addComponent<Components::FactionComponent>(factoryID, faction);
        entityManager.addComponent<Components::GarissonComponent>(factoryID);
        entityManager.addComponent<Components::ShieldComponent>(factoryID, 0, 10, shieldRegenRate);
        return factoryID;
    }

    EntityID createPowerPlant(GameEntityManager& entityManager, std::string name = "", sf::Vector2f position = sf::Vector2f(0.f, 0.f), Components::Faction faction = Components::Faction::NEUTRAL, float shieldRegenRate = 1.f, unsigned int energyCapacity=10) {
        EntityID powerPlantID = entityManager.createEntity();
        entityManager.addComponent<Components::PowerPlantComponent>(powerPlantID, name,energyCapacity);
        entityManager.addComponent<Components::TransformComponent>(powerPlantID, position, 0, sf::Vector2f(1, 1));
        auto shape = sf::CircleShape(Config::POWER_PLANT_RADIUS);
        sf::Color color{100,100,100};
        shape.setFillColor(color);
        shape.setOrigin(Config::POWER_PLANT_RADIUS, Config::POWER_PLANT_RADIUS);
        entityManager.addComponent<Components::ShapeComponent>(powerPlantID, std::make_shared<sf::CircleShape>(shape));
        entityManager.addComponent<Components::LabelComponent>(powerPlantID, name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::POWER_PLANT_RADIUS*2, -2*float(Config::POWER_PLANT_RADIUS))
        );
        entityManager.addComponent<Components::HoverComponent>(powerPlantID);
        entityManager.addComponent<Components::SelectableComponent>(powerPlantID );
        entityManager.addComponent<Components::FactionComponent>(powerPlantID, faction);
        entityManager.addComponent<Components::GarissonComponent>(powerPlantID);

        float maxShield = energyCapacity;
        entityManager.addComponent<Components::ShieldComponent>(powerPlantID, 0, maxShield, shieldRegenRate);
        return powerPlantID;
    }

    EntityID createDrone(GameEntityManager& entityManager, std::string name = "", Components::Faction faction = Components::Faction::NEUTRAL) {
        EntityID droneID = entityManager.createEntity();
        
        entityManager.addComponent<Components::DroneComponent>(droneID, name);
        entityManager.addComponent<Components::TransformComponent>(droneID, sf::Vector2f(0.f,0.f), 0.f, sf::Vector2f(1, 1));
        auto shape = std::make_shared<sf::ConvexShape>();
        shape->setPointCount(3);
        shape->setOrigin(sf::Vector2f(0.f, 0.f));
        shape->setPoint(0, sf::Vector2f(0.f, -Config::DRONE_LENGTH));  // Top point
        shape->setPoint(1, sf::Vector2f(-Config::DRONE_LENGTH, Config::DRONE_LENGTH)); // Bottom-left point
        shape->setPoint(2, sf::Vector2f(Config::DRONE_LENGTH, Config::DRONE_LENGTH));  // Bottom-right point
        sf::Color color{100,100,100};
        shape->setFillColor(color);
        entityManager.addComponent<Components::ShapeComponent>(droneID, shape);
        entityManager.addComponent<Components::LabelComponent>(droneID, name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::DRONE_LENGTH*2, 5)
        );

        entityManager.addComponent<Components::MoveComponent>(droneID, Config::DRONE_SPEED, 0.f);
        entityManager.addComponent<Components::FactionComponent>(droneID, faction);

        return droneID;
    }
    
}


#endif // BUILDER_HPP