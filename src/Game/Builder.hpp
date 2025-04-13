#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <unordered_map>
#include <string>


#include "Components/UnitTypeComponent.hpp"
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
        entityManager.addComponent<Components::UnitTypeComponent>(factoryID, Components::UnitType::Factory);
        entityManager.addComponent<Components::TransformComponent>(factoryID, position, 0.f, sf::Vector2f(1, 1));        
        entityManager.addComponent<Components::HoverableComponent>(factoryID);
        entityManager.addComponent<Components::SelectableComponent>(factoryID);
        entityManager.addComponent<Components::FactionComponent>(factoryID, faction);
        entityManager.addComponent<Components::GarissonComponent>(factoryID);
        entityManager.addComponent<Components::AttackOrderComponent>(factoryID);
        entityManager.addComponent<Components::ShieldComponent>(factoryID, 0, 10, shieldRegenRate);
        entityManager.addComponent<Components::LabelComponent>(factoryID, name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::FACTORY_SIZE+5, - float(Config::FACTORY_SIZE))
        );

        // Sprite
        entityManager.addComponent<Components::SpriteComponent>(factoryID);

        return factoryID;
    }

    EntityID createPowerPlant(GameEntityManager& entityManager, std::string name = "", sf::Vector2f position = sf::Vector2f(0.f, 0.f), Components::Faction faction = Components::Faction::NEUTRAL, float shieldRegenRate = 1.f, unsigned int energyCapacity=10) {
        EntityID powerPlantID = entityManager.createEntity();
        entityManager.addComponent<Components::PowerPlantComponent>(powerPlantID, name,energyCapacity);
        entityManager.addComponent<Components::UnitTypeComponent>(powerPlantID, Components::UnitType::PowerPlant);
        entityManager.addComponent<Components::TransformComponent>(powerPlantID, position, 0, sf::Vector2f(1, 1));
        entityManager.addComponent<Components::LabelComponent>(powerPlantID, name, 
            Resource::ResourceManager::getInstance().getFont(Resource::Paths::FONT_TOXIGENESIS), 
            18, 
            sf::Color::White, 
            sf::Vector2f(Config::POWER_PLANT_RADIUS*2, -2*float(Config::POWER_PLANT_RADIUS))
        );
        entityManager.addComponent<Components::HoverableComponent>(powerPlantID);
        entityManager.addComponent<Components::SelectableComponent>(powerPlantID );
        entityManager.addComponent<Components::FactionComponent>(powerPlantID, faction);
        entityManager.addComponent<Components::GarissonComponent>(powerPlantID);
        entityManager.addComponent<Components::AttackOrderComponent>(powerPlantID);

        float maxShield = energyCapacity;
        entityManager.addComponent<Components::ShieldComponent>(powerPlantID, 0, maxShield, shieldRegenRate);
        
        // Sprite
        entityManager.addComponent<Components::SpriteComponent>(powerPlantID);
        
        return powerPlantID;
    }

    EntityID createDrone(GameEntityManager& entityManager, std::string name = "", Components::Faction faction = Components::Faction::NEUTRAL) {
        EntityID droneID = entityManager.createEntity();
        
        entityManager.addComponent<Components::DroneComponent>(droneID, name);
        entityManager.addComponent<Components::UnitTypeComponent>(droneID, Components::UnitType::Drone);
        entityManager.addComponent<Components::TransformComponent>(droneID, sf::Vector2f(0.f,0.f), 0.f, sf::Vector2f(1, 1));
        entityManager.addComponent<Components::MoveComponent>(droneID, Config::DRONE_SPEED, 0.f);
        entityManager.addComponent<Components::FactionComponent>(droneID, faction);
        entityManager.addComponent<Components::AttackOrderComponent>(droneID);

        // Sprite
        entityManager.addComponent<Components::SpriteComponent>(droneID);

        return droneID;
    }

    EntityID createExplosionAnimation(GameEntityManager& manager, sf::Vector2f position = sf::Vector2f(0.f, 0.f)){
        // Add explosion animation
        EntityID animID = manager.createEntity();
        manager.addComponent<Components::TransformComponent>(animID, position, 0.f, sf::Vector2f(3, 3));
        manager.addComponent<Components::SpriteComponent>(animID);
        auto* sprite = manager.getComponent<Components::SpriteComponent>(animID);
        sprite->sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_EXPLOSIONS_ATLAS));
        sprite->sprite.setTextureRect(sf::IntRect(0, 0, 1, 1));
        sprite->layer = 1;
        manager.addComponent<Components::AnimationComponent>(animID, "expl_11", 24, false, 0.05f);
        return animID;
    }
}


#endif // BUILDER_HPP