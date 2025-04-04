#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <unordered_map>
#include <string>



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


    inline void assignSprite(Components::SpriteComponent* spriteComp, const std::string& texturePath, const std::string& atlasPath, const std::string& name) {
        const auto& texture = Resource::ResourceManager::getInstance().getTexture(texturePath);
        const auto& atlas = Resource::ResourceManager::getInstance().getAtlas(atlasPath);

        spriteComp->sprite.setTexture(texture);
        auto rect = atlas.getRect(name);
        spriteComp->sprite.setTextureRect(rect);
        spriteComp->sprite.setOrigin(rect.width/2, rect.height/2);
    }

    EntityID createFactory(GameEntityManager& entityManager, std::string name = "", sf::Vector2f position = sf::Vector2f(0.f, 0.f), Components::Faction faction = Components::Faction::NEUTRAL, float productionRate = 1.f, float shieldRegenRate = 1.f) {
        // Create Factory
        EntityID factoryID = entityManager.createEntity();

        entityManager.addComponent<Components::FactoryComponent>(factoryID, name, productionRate);
        entityManager.addComponent<Components::TransformComponent>(factoryID, position, 0.f, sf::Vector2f(1, 1));
        entityManager.addComponent<Components::HoverComponent>(factoryID);
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
        auto spriteComp = entityManager.getComponent<Components::SpriteComponent>(factoryID);
        // TODO: need some sort of color for the faction
        assignSprite(spriteComp, Resource::Paths::TEXTURE_SPACE_EXTENSION, Resource::Paths::ATLAS_SPACE_EXTENSION, "spaceStation_020.png");
        auto transformComp = entityManager.getComponent<Components::TransformComponent>(factoryID);
        transformComp->transform.setScale(sf::Vector2f(0.25f, 0.25f));

        return factoryID;
    }

    EntityID createPowerPlant(GameEntityManager& entityManager, std::string name = "", sf::Vector2f position = sf::Vector2f(0.f, 0.f), Components::Faction faction = Components::Faction::NEUTRAL, float shieldRegenRate = 1.f, unsigned int energyCapacity=10) {
        EntityID powerPlantID = entityManager.createEntity();
        entityManager.addComponent<Components::PowerPlantComponent>(powerPlantID, name,energyCapacity);
        entityManager.addComponent<Components::TransformComponent>(powerPlantID, position, 0, sf::Vector2f(1, 1));
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
        entityManager.addComponent<Components::AttackOrderComponent>(powerPlantID);

        float maxShield = energyCapacity;
        entityManager.addComponent<Components::ShieldComponent>(powerPlantID, 0, maxShield, shieldRegenRate);
        
        // Sprite
        entityManager.addComponent<Components::SpriteComponent>(powerPlantID);
        auto spriteComp = entityManager.getComponent<Components::SpriteComponent>(powerPlantID);
        assignSprite(spriteComp, Resource::Paths::TEXTURE_SPACE_EXTENSION, Resource::Paths::ATLAS_SPACE_EXTENSION, "spaceStation_023.png");

        auto transformComp = entityManager.getComponent<Components::TransformComponent>(powerPlantID);
        transformComp->transform.setScale(sf::Vector2f(0.5f, 0.5f));

        return powerPlantID;
    }

    EntityID createDrone(GameEntityManager& entityManager, std::string name = "", Components::Faction faction = Components::Faction::NEUTRAL) {
        EntityID droneID = entityManager.createEntity();
        
        entityManager.addComponent<Components::DroneComponent>(droneID, name);
        entityManager.addComponent<Components::TransformComponent>(droneID, sf::Vector2f(0.f,0.f), 0.f, sf::Vector2f(1, 1));
        entityManager.addComponent<Components::MoveComponent>(droneID, Config::DRONE_SPEED, 0.f);
        entityManager.addComponent<Components::FactionComponent>(droneID, faction);
        entityManager.addComponent<Components::AttackOrderComponent>(droneID);

        // Sprite
        entityManager.addComponent<Components::SpriteComponent>(droneID);
        auto spriteComp = entityManager.getComponent<Components::SpriteComponent>(droneID);
        assignSprite(spriteComp, Resource::Paths::TEXTURE_SPACE, Resource::Paths::ATLAS_SPACE, "playerShip3_red.png");
         
        auto transformComp = entityManager.getComponent<Components::TransformComponent>(droneID);
        transformComp->transform.setScale(sf::Vector2f(0.35f, 0.35f));

        return droneID;
    }
    
}


#endif // BUILDER_HPP