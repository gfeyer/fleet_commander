#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Config.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/SelectableComponent.hpp"

#include "Utils/Logger.hpp"

namespace Systems {
    void InputSelectionSystem(const sf::Event& event, std::unordered_map<EntityID, Entity>& entities, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Get the click position in world coordinates
            sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            // determine if there is already a selection
            bool selectionExists = false;
            EntityID selectedEntityID = -1;
            for (auto& [id, entity] : entities) {
                auto* selectableComp = entity.getComponent<Components::SelectableComponent>();
                if (selectableComp && selectableComp->isSelected) {
                    selectionExists = true;
                    selectedEntityID = id;
                    break;
                }
            }

            // Determine if a new selection was made
            for (auto& [id, entity] : entities) {
                auto* transform = entity.getComponent<Components::TransformComponent>();
                auto* shapeComp = entity.getComponent<Components::ShapeComponent>();
                auto* selectableComp = entity.getComponent<Components::SelectableComponent>();

                if (transform && shapeComp && selectableComp) {
                    // Check if mouse is within entity bounds
                    if (shapeComp->shape->getGlobalBounds().contains(worldPos)) {
                        if (selectionExists && selectedEntityID != id) {
                            log_info << "Attack entity " << id << " from " << selectedEntityID;

                            auto* factory = entities.at(selectedEntityID).getComponent<Components::FactoryComponent>();
                            if(factory){
                                for(auto it = factory->drones.begin(); it != factory->drones.end();){
                                    auto* moveComp = entities.at(*it).getComponent<Components::MoveComponent>();
                                    if(moveComp){
                                        moveComp->targetPosition = worldPos;
                                        moveComp->moveToTarget = true;
                                        it = factory->drones.erase(it);
                                    }else{
                                        ++it;
                                    }
                                }
                            }
                        }else{
                            // log_info << "Select entity " << id;
                            selectableComp->isSelected = true;
                        }
                    } else {
                        selectableComp->isSelected = false;
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