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

#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"

namespace Systems {

    EntityID getPreviouslySelectedEntity(Game::GameEntityManager& entityManager){

        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {
            auto* selectableComp = entity.getComponent<Components::SelectableComponent>();
            if (selectableComp && selectableComp->isSelected) {
                return id;
            }
        }
        return -1;
    }

    EntityID getSelectedEntity(const sf::Event& event, Game::GameEntityManager& entityManager, const sf::RenderWindow& window){
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        auto& entities = entityManager.getAllEntities();
        // Determine if a new selection was made
        for (auto& [targetID, targetEntity] : entities) {
            auto* targetTransform = targetEntity.getComponent<Components::TransformComponent>();
            auto* targetShapeComp = targetEntity.getComponent<Components::ShapeComponent>();
            auto* targetSelectableComp = targetEntity.getComponent<Components::SelectableComponent>();

            if (targetTransform && targetShapeComp && targetSelectableComp) {
                    // Check if mouse is within entity bounds (eg. click on entity)
                if (targetShapeComp->shape->getGlobalBounds().contains(worldPos)){
                    return targetID;
                }
            }
        }
        return -1;
    }

    void InputSelectionSystem(const sf::Event& event, Game::GameEntityManager& entityManager, const sf::RenderWindow& window) {

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Get the click position in world coordinates
            
            EntityID previouslySelectedEntityID = getPreviouslySelectedEntity(entityManager);
            EntityID selectedEntityID = getSelectedEntity(event, entityManager, window);

            if(previouslySelectedEntityID != -1 && selectedEntityID == -1){
                // A target already has been selected previously
                // No new target is selected now
                // Cancel old selection
                entityManager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;

            }else if (previouslySelectedEntityID != -1 && previouslySelectedEntityID != selectedEntityID) {
                // A target has already been selected previously
                // This new selection is different than the old one
                // Add attack orders

                // log_info << "Attack entity " << selectedEntityID << " from " << previouslySelectedEntityID;              
                Entity& originEntity = entityManager.getEntity(previouslySelectedEntityID);
                auto* factionComp = originEntity.getComponent<Components::FactionComponent>();
                if(factionComp->faction == Components::Faction::PLAYER_1){
                    entityManager.addComponent(previouslySelectedEntityID, Components::AttackOrderComponent{previouslySelectedEntityID, selectedEntityID});
                }               
                // deselect targets after attack order
                entityManager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;
                entityManager.getComponent<Components::SelectableComponent>(selectedEntityID)->isSelected = false;

            }else if(previouslySelectedEntityID == -1 && selectedEntityID != -1){
                // A target has not been selected previously
                // This is the first selection
                // Select the target
                Entity& targetEntity = entityManager.getEntity(selectedEntityID);
                auto* factionComp = targetEntity.getComponent<Components::FactionComponent>();
                if(factionComp->faction == Components::Faction::PLAYER_1){
                    entityManager.getComponent<Components::SelectableComponent>(selectedEntityID)->isSelected = true;
                }
            }else{
                // do nothing
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            EntityID previouslySelectedEntityID = getPreviouslySelectedEntity(entityManager);
            EntityID selectedEntityID = getSelectedEntity(event, entityManager, window);

            if(previouslySelectedEntityID != -1 && selectedEntityID == -1){
                // A target already has been selected previously
                // No new target is selected now
                // Cancel old selection and orders
                auto* transferComp = entityManager.getComponent<Components::DroneTransferComponent>(previouslySelectedEntityID);
                if(transferComp){
                    entityManager.removeComponent<Components::DroneTransferComponent>(previouslySelectedEntityID);
                }
                // deselect
                entityManager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;

            }else if(previouslySelectedEntityID != -1 && previouslySelectedEntityID != selectedEntityID){
                // A target has already been selected previously
                // This new selection is different than the old one
                // Add transfer orders

                auto* sourceGarissonComp = entityManager.getComponent<Components::GarissonComponent>(previouslySelectedEntityID);
                auto* targetGarissonComp = entityManager.getComponent<Components::GarissonComponent>(selectedEntityID);
                // auto* sourceTransferComp = entityManager.getComponent<Components::DroneTransferComponent>(previouslySelectedEntityID);

                if(sourceGarissonComp && targetGarissonComp){
                    auto* factionComp = entityManager.getEntity(previouslySelectedEntityID).getComponent<Components::FactionComponent>();

                    if(factionComp->faction == Components::Faction::PLAYER_1){
                        entityManager.addComponent(previouslySelectedEntityID, Components::DroneTransferComponent(previouslySelectedEntityID, selectedEntityID, factionComp->faction));
                    }
                }

                // deselect both targets
                entityManager.getComponent<Components::SelectableComponent>(previouslySelectedEntityID)->isSelected = false;
                entityManager.getComponent<Components::SelectableComponent>(selectedEntityID)->isSelected = false;
            }
        }
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