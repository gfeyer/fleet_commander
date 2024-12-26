#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Config.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/Builder.hpp"

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
            for (auto& [id, entity] : entities) {
                auto* targetTransform = entity.getComponent<Components::TransformComponent>();
                auto* targetShapeComp = entity.getComponent<Components::ShapeComponent>();
                auto* targetSelectableComp = entity.getComponent<Components::SelectableComponent>();

                if (targetTransform && targetShapeComp && targetSelectableComp) {
                    // Check if mouse is within entity bounds
                    if (targetShapeComp->shape->getGlobalBounds().contains(worldPos)) {
                        if (originSelectionExists && originEntityID != id) {
                            log_info << "Attack entity " << id << " from " << originEntityID;

                            auto* originFactory = entities.at(originEntityID).getComponent<Components::FactoryComponent>();
                            auto* originFaction = entities.at(originEntityID).getComponent<Components::FactionComponent>();
                            auto* originTransform = entities.at(originEntityID).getComponent<Components::TransformComponent>();
                            if(originFactory && originFaction && originFactory->stationedDrones > 0){
                                auto totalDrones = originFactory->stationedDrones;

                                for(int i=0; i < totalDrones; i++){
                                    auto drone = Builder::createDrone(std::string("D") + std::to_string(i), originFaction->factionID);
                                    drone.getComponent<Components::TransformComponent>()->transform.setPosition(originTransform->getPosition());
                                    auto* moveComp = drone.getComponent<Components::MoveComponent>();
                                    moveComp->targetPosition = targetTransform->getPosition();
                                    moveComp->moveToTarget = true;
                                    entities.emplace(drone.id, std::move(drone));
                                }

                                originFactory->stationedDrones = 0;
                            }
                        }else{
                            // log_info << "Select entity " << id;
                            targetSelectableComp->isSelected = true;
                        }
                    } else {
                        targetSelectableComp->isSelected = false;
                        // log_info << "Deselected entity " << id;
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