#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Config.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/Builder.hpp"
#include "Components/AttackOrderComponent.hpp"

#include "Utils/Logger.hpp"

namespace Systems {
    void InputSelectionSystem(const sf::Event& event, std::unordered_map<EntityID, Entity>& entities, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Get the click position in world coordinates
            sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            // determine if there is already a selection
            bool originSelectionExists = false;
            EntityID originEntityID = -1;
            for (auto& [id, entity] : entities) {
                auto* selectableComp = entity.getComponent<Components::SelectableComponent>();
                if (selectableComp && selectableComp->isSelected) {
                    originSelectionExists = true;
                    originEntityID = id;
                    break;
                }
            }

            // Determine if a new selection was made
            for (auto& [targetID, targetEntity] : entities) {
                auto* targetTransform = targetEntity.getComponent<Components::TransformComponent>();
                auto* targetShapeComp = targetEntity.getComponent<Components::ShapeComponent>();
                auto* targetSelectableComp = targetEntity.getComponent<Components::SelectableComponent>();

                if (targetTransform && targetShapeComp && targetSelectableComp) {
                    // Check if mouse is within entity bounds
                    if (targetShapeComp->shape->getGlobalBounds().contains(worldPos)) {
                        if (originSelectionExists && originEntityID != targetID) {
                            log_info << "Attack entity " << targetID << " from " << originEntityID;

                            auto* originFaction = entities.at(originEntityID).getComponent<Components::FactionComponent>();
                            auto* originGarisson = entities.at(originEntityID).getComponent<Components::GarissonComponent>();

                            if(originFaction && originGarisson && originGarisson->getDroneCount() > 0){
                                auto totalDrones = originGarisson->getDroneCount();

                                for(auto i=0; i < totalDrones; i++){
                                    auto drone = Builder::createDrone(std::to_string(i), originFaction->factionID);
                                    drone.addComponent(Components::AttackOrderComponent{originEntityID, targetID});
                                    entities.emplace(drone.id, std::move(drone));
                                }

                                originGarisson->setDroneCount(0);
                            }
                        }else{
                            targetSelectableComp->isSelected = true;
                        }
                    } else {
                        targetSelectableComp->isSelected = false;
                    }
                }
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