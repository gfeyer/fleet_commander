#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <utility>

#include "Core/Entity.hpp"
#include "Config.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/AttackOrderComponent.hpp"
#include "Components/DroneTransferComponent.hpp"
#include "Components/FactionComponent.hpp"

#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"

namespace Systems {

    EntityID getPreviouslySelectedEntity(Game::GameEntityManager& manager){

        auto entities = manager.getAllEntityIDs();
        for (auto id : entities) {
            auto* selectableComp = manager.getComponent<Components::SelectableComponent>(id);
            if (selectableComp && selectableComp->isSelected) {
                return id;
            }
        }
        return NullEntityID;
    }

    EntityID getSelectedEntity(const sf::Event& event, Game::GameEntityManager& manager, const sf::RenderWindow& window){
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        auto entities = manager.getAllEntityIDs();
        // Determine if a new selection was made
        for (auto targetID : entities) {
            auto* targetTransform = manager.getComponent<Components::TransformComponent>(targetID);
            auto* targetShapeComp = manager.getComponent<Components::ShapeComponent>(targetID);
            auto* targetSelectableComp = manager.getComponent<Components::SelectableComponent>(targetID);

            if (targetTransform && targetShapeComp && targetSelectableComp) {
                    // Check if mouse is within entity bounds (eg. click on entity)
                if (targetShapeComp->shape->getGlobalBounds().contains(worldPos)){
                    return targetID;
                }
            }
        }
        return NullEntityID;
    }

    void InputSelectionSystem(const sf::Event& event, Game::GameEntityManager& manager, const sf::RenderWindow& window) {

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Get the click position in world coordinates
            
            EntityID previouslySelectedEntityID = getPreviouslySelectedEntity(manager);
            EntityID selectedEntityID = getSelectedEntity(event, manager, window);

            if(previouslySelectedEntityID != NullEntityID && selectedEntityID == NullEntityID){
                // A target already has been selected previously
                // No new target is selected now
                // Cancel old selection
                manager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;

            }else if (previouslySelectedEntityID != NullEntityID && previouslySelectedEntityID != selectedEntityID) {
                // A target has already been selected previously
                // This new selection is different than the old one
                // Add attack orders

                // log_info << "Attack entity " << selectedEntityID << " from " << previouslySelectedEntityID;              
                auto* factionComp = manager.getComponent<Components::FactionComponent>(previouslySelectedEntityID);
                if(factionComp->faction == Components::Faction::PLAYER_1){
                    manager.addOrReplaceComponent<Components::AttackOrderComponent>(previouslySelectedEntityID, previouslySelectedEntityID, selectedEntityID);
                }               
                // deselect targets after attack order
                manager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;
                manager.getComponent<Components::SelectableComponent>(selectedEntityID)->isSelected = false;

            }else if(previouslySelectedEntityID == NullEntityID && selectedEntityID != NullEntityID){
                // A target has not been selected previously
                // This is the first selection
                // Select the target
                auto* factionComp = manager.getComponent<Components::FactionComponent>(selectedEntityID);
                if(factionComp->faction == Components::Faction::PLAYER_1){
                    manager.getComponent<Components::SelectableComponent>(selectedEntityID)->isSelected = true;
                }
            }else{
                // do nothing
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            EntityID previouslySelectedEntityID = getPreviouslySelectedEntity(manager);
            EntityID selectedEntityID = getSelectedEntity(event, manager, window);

            if(previouslySelectedEntityID != NullEntityID && selectedEntityID == NullEntityID){
                // A target already has been selected previously
                // No new target is selected now
                // Cancel old selection and orders
                auto* transferComp = manager.getComponent<Components::DroneTransferComponent>(previouslySelectedEntityID);
                if(transferComp){
                    manager.removeComponent<Components::DroneTransferComponent>(previouslySelectedEntityID);
                }
                // deselect
                manager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;

            }else if(previouslySelectedEntityID != NullEntityID && previouslySelectedEntityID != selectedEntityID){
                // A target has already been selected previously
                // This new selection is different than the old one
                // Add transfer orders

                auto* sourceGarissonComp = manager.getComponent<Components::GarissonComponent>(previouslySelectedEntityID);
                auto* targetGarissonComp = manager.getComponent<Components::GarissonComponent>(selectedEntityID);
                // auto* sourceTransferComp = entityManager.getComponent<Components::DroneTransferComponent>(previouslySelectedEntityID);

                if(sourceGarissonComp && targetGarissonComp){
                    auto* factionComp = manager.getComponent<Components::FactionComponent>(previouslySelectedEntityID);

                    if(factionComp->faction == Components::Faction::PLAYER_1){
                        log_info << "adding trasnfer component";
                        manager.addOrReplaceComponent<Components::DroneTransferComponent>(previouslySelectedEntityID, previouslySelectedEntityID, selectedEntityID, factionComp->faction);
                    }
                }

                // deselect both targets
                manager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;
                manager.getComponent<Components::SelectableComponent>(selectedEntityID)->isSelected = false;
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