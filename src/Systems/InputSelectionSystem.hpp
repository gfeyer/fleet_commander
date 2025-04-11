#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <cassert>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <utility>


#include "Config.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/AttackOrderComponent.hpp"
#include "Components/DroneTransferComponent.hpp"
#include "Components/FactionComponent.hpp"

#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"

namespace Systems {

    EntityID getPreviouslySelectedEntity(Game::GameEntityManager& manager){

        for(auto&& [id] : manager.view<Components::SelectedComponent>().each()){
            return id;
        }
        return NullEntityID;
    }

    EntityID getSelectedEntity(const sf::Event& event, Game::GameEntityManager& manager, const sf::RenderWindow& window){
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        for(auto&& [id, sprite] : manager.view<Components::SpriteComponent, Components::SelectableComponent>().each()){
            if(sprite.sprite.getGlobalBounds().contains(worldPos)){
                return id;
            }
        }
        return NullEntityID;
    }

    void InputSelectionSystem(const sf::Event& event, Game::GameEntityManager& manager, const sf::RenderWindow& window) {
        
        for(auto&& [id] : manager.view<Components::SelectedComponent>().each()){
            log_info << "selection: " << entt::to_integral(id);
        }

        if(event.type != sf::Event::MouseButtonPressed){
            return;
        }

        EntityID previousSelection = getPreviouslySelectedEntity(manager);
        EntityID currentSelection = getSelectedEntity(event, manager, window);

        log_info << "Previous Selection: " << entt::to_integral(previousSelection) << " Current Selection: " << entt::to_integral(currentSelection);

        if(previousSelection == NullEntityID && currentSelection == NullEntityID){
            // No selection, do nothing
            return;
        }

        if(previousSelection == currentSelection){
            // Clicked same entity, do nothing
            return;
        }

        if(previousSelection == NullEntityID && currentSelection != NullEntityID){
            // A target has not been selected previously
            // This is the first selection
            // The first selection must always be player_1, cannot select enemy or neutral as a first selection
            auto* factionComp = manager.getComponent<Components::FactionComponent>(currentSelection);
            if(factionComp->faction == Components::Faction::PLAYER_1){
                manager.addOrReplaceComponent<Components::SelectedComponent>(currentSelection);
            }
        }

        // Left Click
        if (event.mouseButton.button == sf::Mouse::Left){

            if(previousSelection != NullEntityID && currentSelection == NullEntityID){
                // A target already has been selected previously
                // No new target is selected now
                // Cancel old selection
                manager.removeComponent<Components::SelectedComponent>(previousSelection);
                return;
            }

            if(previousSelection != NullEntityID && currentSelection != NullEntityID){
                // A target has already been selected previously
                // This new selection is different than the old one
                // Add attack orders
                
                // log_info << "Attack entity " << selectedEntityID << " from " << previouslySelectedEntityID;              
                auto* factionComp = manager.getComponent<Components::FactionComponent>(previousSelection);
                if(factionComp->faction == Components::Faction::PLAYER_1){
                    manager.addOrReplaceComponent<Components::AttackOrderComponent>(previousSelection, previousSelection, currentSelection);
                }

                // deselect targets after attack order
                manager.removeComponent<Components::SelectedComponent>(previousSelection);
                manager.removeComponent<Components::SelectedComponent>(currentSelection);
                return;
            }
        }

        // Right click
        if(event.mouseButton.button == sf::Mouse::Right){

            if(previousSelection != NullEntityID && currentSelection == NullEntityID){
                // A target already has been selected previously
                // No new target is selected now
                // Cancel old selection and orders

                auto* transferComp = manager.getComponent<Components::DroneTransferComponent>(previousSelection);
                if(transferComp){
                    manager.removeComponent<Components::DroneTransferComponent>(previousSelection);
                }

                // deselect
                manager.removeComponent<Components::SelectedComponent>(previousSelection);
                return;
            }

            if(previousSelection != NullEntityID && currentSelection != NullEntityID){
                // A target has already been selected previously
                // This new selection is different than the old one
                // Add transfer orders

                auto* sourceGarissonComp = manager.getComponent<Components::GarissonComponent>(previousSelection);
                auto* targetGarissonComp = manager.getComponent<Components::GarissonComponent>(currentSelection);

                if(sourceGarissonComp && targetGarissonComp){
                    auto* factionComp = manager.getComponent<Components::FactionComponent>(previousSelection);

                    if(factionComp->faction == Components::Faction::PLAYER_1){
                        // log_info << "adding transfer component...";
                        manager.addOrReplaceComponent<Components::DroneTransferComponent>(previousSelection, previousSelection, currentSelection, factionComp->faction);
                    }
                }

                // deselect both targets
                manager.removeComponent<Components::SelectedComponent>(previousSelection);
                manager.removeComponent<Components::SelectedComponent>(currentSelection);
                return;
            }
        }

        /* -- Debug --
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle){
            auto selectedEntityID = getSelectedEntity(event, manager, window);
            if(selectedEntityID != NullEntityID){
                auto* factionComp = manager.getComponent<Components::FactionComponent>(selectedEntityID);

                if(factionComp->faction == Components::Faction::PLAYER_1){
                    factionComp->faction = Components::Faction::PLAYER_2;
                }
                else{
                    factionComp->faction = Components::Faction::PLAYER_1;
                }

            }
        } */ 
    }
}

#endif // INPUT_SYSTEM_HPP


/*
for (auto& [id, entity] : entities) {
                auto* move = entity.getComponent<Components::MoveComponent>();
                if (move) {
                    move->targetPosition = clickPosition;
                    move->moveToTarget = true;
                }
            }
*/