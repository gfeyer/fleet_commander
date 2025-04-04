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
            float scaleFactor = 0.20f;
            switch (typeComp.type)
            {
            case Components::UnitType::PowerPlant:
            {
                const auto& textureRed = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_POWER_STATION_RED);
                if(factionComp.faction == Components::Faction::PLAYER_1) {
                    spriteComp.sprite.setTexture(textureRed, true);
                    spriteComp.sprite.setColor(sf::Color::Red);
                }else if(factionComp.faction == Components::Faction::PLAYER_2) {
                    spriteComp.sprite.setTexture(textureRed, true);
                    spriteComp.sprite.setColor(sf::Color::Blue);
                }else{
                    spriteComp.sprite.setTexture(textureRed, true);
                }
                transformComp.transform.setScale(scaleFactor,scaleFactor);
                spriteComp.sprite.setOrigin(textureRed.getSize().x/2, textureRed.getSize().y/2);
                break;
            }
            case Components::UnitType::Factory:
            {
                const auto& textureRed = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_FACTORY_RED);
                if(factionComp.faction == Components::Faction::PLAYER_1) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_FACTORY_RED), true);
                    spriteComp.sprite.setColor(sf::Color::Red);
                }else if(factionComp.faction == Components::Faction::PLAYER_2) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_FACTORY_RED), true);
                    spriteComp.sprite.setColor(sf::Color::Blue);
                }else{
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_FACTORY_RED), true);
                }
                transformComp.transform.setScale(scaleFactor,scaleFactor);
                spriteComp.sprite.setOrigin(textureRed.getSize().x/2, textureRed.getSize().y/2);
                break;
            }
            case Components::UnitType::Drone:
            {
                const auto& textureRed = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_DRONE_RED);
                if(factionComp.faction == Components::Faction::PLAYER_1) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_DRONE_RED));
                    spriteComp.sprite.setColor(sf::Color::Red);
                }else if(factionComp.faction == Components::Faction::PLAYER_2) {
                    spriteComp.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_DRONE_RED));
                    spriteComp.sprite.setColor(sf::Color::Blue);
                }else{ }
                transformComp.transform.setScale(scaleFactor/2,scaleFactor/2);
                spriteComp.sprite.setOrigin(textureRed.getSize().x/2, textureRed.getSize().y/2);
                break;
            }
            default:
                break;
            }
        }

        // TODO:
        // for (auto&& [id, spriteComp, selectable] : manager.view<Components::SpriteComponent, Components::SelectableComponent>().each()) {
        //     if (selectable.isSelected) {
                
        //     }
        // }

    }
}

#endif // SYSTEMS_SPRITE_UPDATE_SYSTEM_HPP