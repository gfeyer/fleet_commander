#ifndef SYSTEMS_SPRITE_UPDATE_SYSTEM_HPP
#define SYSTEMS_SPRITE_UPDATE_SYSTEM_HPP

#include "Game/GameEntityManager.hpp"

#include "Components/SpriteComponent.hpp"
#include "Components/FactionComponent.hpp"
#include "Components/PowerPlantComponent.hpp"

namespace Systems {

    inline void assignSprite(Components::SpriteComponent& spriteComp, const std::string& texturePath, const std::string& atlasPath, const std::string& name) {
        const auto& texture = Resource::ResourceManager::getInstance().getTexture(texturePath);
        const auto& atlas = Resource::ResourceManager::getInstance().getAtlas(atlasPath);

        spriteComp.sprite.setTexture(texture);
        auto rect = atlas.getRect(name);
        spriteComp.sprite.setTextureRect(rect);
        spriteComp.sprite.setOrigin(rect.width/2, rect.height/2);
    }

    void SpriteUpdateSystem(Game::GameEntityManager& manager) {

        for (auto&& [id, spriteComp, factionComp, typeComp, transformComp] : manager.view<Components::SpriteComponent, Components::FactionComponent, Components::UnitTypeComponent, Components::TransformComponent>().each()) {
            
            switch (typeComp.type)
            {
            case Components::UnitType::PowerPlant:
                if(factionComp.faction == Components::Faction::PLAYER_1) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_POWER_PLANT_RED), true);
                    transformComp.transform.setScale(0.5f, 0.5f);

                }else if(factionComp.faction == Components::Faction::PLAYER_2) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_POWER_PLANT_BLUE), true);
                    transformComp.transform.setScale(0.5f, 0.5f);

                }else{
                    assignSprite(spriteComp, Resource::Paths::TEXTURE_SPACE_EXTENSION, Resource::Paths::ATLAS_SPACE_EXTENSION, "spaceStation_023.png");
                    transformComp.transform.setScale(0.5f, 0.5f); 
                }
                break;
            case Components::UnitType::Factory:
                if(factionComp.faction == Components::Faction::PLAYER_1) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_FACTORY_RED), true);
                    transformComp.transform.setScale(0.5f, 0.5f);
                }else if(factionComp.faction == Components::Faction::PLAYER_2) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_FACTORY_BLUE), true);
                    transformComp.transform.setScale(0.5f, 0.5f);
                }else{
                    assignSprite(spriteComp, Resource::Paths::TEXTURE_SPACE_EXTENSION, Resource::Paths::ATLAS_SPACE_EXTENSION, "spaceStation_015.png");
                    spriteComp.sprite.setColor(sf::Color::White);
                    transformComp.transform.setScale(0.25f, 0.25f);
                }
                break;
            case Components::UnitType::Drone:
                if(factionComp.faction == Components::Faction::PLAYER_1) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_DRONE_RED));
                    transformComp.transform.setScale(0.15f, 0.15f);
                }else if(factionComp.faction == Components::Faction::PLAYER_2) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_DRONE_BLUE));
                    transformComp.transform.setScale(0.15f, 0.15f);
                }else{ 

                }
                break;
            default:
                break;
            }
        }
    }
}

#endif // SYSTEMS_SPRITE_UPDATE_SYSTEM_HPP