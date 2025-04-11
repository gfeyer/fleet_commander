#ifndef INPUT_HOVER_SYSTEM_HPP
#define INPUT_HOVER_SYSTEM_HPP

#include <unordered_map>
#include <cassert>
#include <SFML/Graphics.hpp>


#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/CursorComponent.hpp"

#include "Utils/Logger.hpp"

#include "Game/GameEntityManager.hpp"

namespace Systems {


    void InputHoverSystem(Game::GameEntityManager& manager, const sf::RenderWindow& window) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        // Remove hovered component
        for (auto&& [id, sprite, hovered]: manager.view<Components::SpriteComponent, Components::HoveredComponent>().each()) {
            if (!sprite.sprite.getGlobalBounds().contains(worldPos)) {
                manager.removeComponent<Components::HoveredComponent>(id);
            }
        }
        
        EntityID hoveredEntity = NullEntityID;
        // Add hovered component
        for (auto&& [id, sprite]: manager.view<Components::SpriteComponent, Components::HoverableComponent>().each()) {
            if (sprite.sprite.getGlobalBounds().contains(worldPos)) {
                auto hoverPosition = static_cast<sf::Vector2f>(mousePos);
                manager.addOrReplaceComponent<Components::HoveredComponent>(id, hoverPosition);
                hoveredEntity = id;
            }
        }

        if(hoveredEntity == NullEntityID){
            return;
        }

        // Get selection, cursor and faction
        EntityID selection = NullEntityID;
        EntityID cursor = NullEntityID;

        for(auto&& [id] : manager.view<Components::SelectedComponent>().each()){
            selection = id;
        }
        
        for(auto&& [id, c] : manager.view<Components::CursorComponent>().each()){
            c.type = Components::CursorType::NONE;
            cursor = id;
        }
        
        auto* hoveredFaction = manager.getComponent<Components::FactionComponent>(hoveredEntity);
        auto* selectedFaction = manager.getComponent<Components::FactionComponent>(selection);
        auto* cursorComp = manager.getComponent<Components::CursorComponent>(cursor);

        if(selection == NullEntityID){
            // Nothing is selected
            // Only display friendly cursor if hovered entity is friendly otherwise none
            if(hoveredFaction->faction == Components::Faction::PLAYER_1){
                cursorComp->type = Components::CursorType::FRIENDLY;
            }
        }else{
            // There is a previous selection here
            if(selectedFaction->faction == Components::Faction::PLAYER_1 && hoveredFaction->faction != Components::Faction::PLAYER_1){
                cursorComp->type = Components::CursorType::ATTACK;
            }else{
                cursorComp->type = Components::CursorType::FRIENDLY;
            }
        }
    }
}


#endif // INPUT_HOVER_SYSTEM_HPP