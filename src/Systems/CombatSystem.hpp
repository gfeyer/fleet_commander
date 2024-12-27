#ifndef COMBAT_SYSTEM_HPP
#define COMBAT_SYSTEM_HPP

#include <unordered_map>
#include <unordered_set>

#include "Core/Entity.hpp"

#include "Components/MoveComponent.hpp"
#include "Components/AttackOrderComponent.hpp"
#include "Components/GarissonComponent.hpp"
#include "Core/Entity.hpp"

#include "Utils/Logger.hpp"

namespace Systems {
        void CombatSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {

            std::unordered_set<EntityID> toRemove;

            for (auto& [id, entity] : entities) {
                auto* attackOrder = entity.getComponent<Components::AttackOrderComponent>();
                auto* garisson = entity.getComponent<Components::GarissonComponent>();
                auto* drone = entity.getComponent<Components::DroneComponent>();
                auto* move = entity.getComponent<Components::MoveComponent>();

                if (attackOrder && garisson) {
                    // Attack order was just palced at a garison
                    // Create drones and send them to the target
                    if (garisson->getDroneCount() < 2) {
                        log_info << "Cannnot attack, not enough drones";
                        entity.removeComponent<Components::AttackOrderComponent>();
                        continue;
                    }

                    auto* originFaction = entities[attackOrder->origin].getComponent<Components::FactionComponent>();

                    // TODO: insert error msg if originFaction is missing
                    auto dronesUsedForAttack = garisson->getDroneCount()-1;

                    for(auto i=0; i < dronesUsedForAttack; i++){
                        auto drone = Builder::createDrone(std::to_string(i), originFaction->factionID);
                        drone.addComponent(Components::AttackOrderComponent{attackOrder->origin, attackOrder->target});
                        auto* transform = drone.getComponent<Components::TransformComponent>();
                        sf::Vector2f startPosition = entities[attackOrder->origin].getComponent<Components::TransformComponent>()->transform.getPosition();
                        int spread = 25 + (dronesUsedForAttack * 5);
                        spread = std::min(spread, 75);
                        sf::Vector2f randomOffset = sf::Vector2f(
                            rand() % (2 * spread) - spread,
                            rand() % (2 * spread) - spread
                        );
                        transform->transform.setPosition(startPosition + randomOffset);

                        auto* move = drone.getComponent<Components::MoveComponent>();
                        move->targetPosition = entities[attackOrder->target].getComponent<Components::TransformComponent>()->transform.getPosition();
                        move->moveToTarget = true;
                        entities.emplace(drone.id, std::move(drone));
                    }
                    garisson->setDroneCount(1);
                    entity.removeComponent<Components::AttackOrderComponent>();
                }
                else if (attackOrder && drone && move) {
                    if (!move->moveToTarget) {
                        log_info << "Drone " << id << " has reached target";
                        // Reached destination
                        auto* targetGarisson = entities[attackOrder->target].getComponent<Components::GarissonComponent>();
                        auto* originFaction = entities[attackOrder->origin].getComponent<Components::FactionComponent>();
                        auto* targetFaction = entities[attackOrder->target].getComponent<Components::FactionComponent>();

                        if (targetGarisson && originFaction && targetFaction) {
                            if(targetGarisson->getDroneCount() == 0){
                                targetFaction->factionID = originFaction->factionID;
                            }

                            if(targetFaction->factionID == originFaction->factionID || targetFaction->factionID == 0){
                                targetGarisson->incrementDroneCount();
                            }else{
                                targetGarisson->decrementDroneCount();
                            }
                            toRemove.insert(id);
                        }
                    }
                }
            }

            for (const auto& id : toRemove) {
                entities.erase(id);
            }
        }

}

#endif // COMBAT_SYSTEM_HPP