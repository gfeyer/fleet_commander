#ifndef COMBAT_SYSTEM_HPP
#define COMBAT_SYSTEM_HPP

#include <unordered_map>
#include <unordered_set>

#include "Core/Entity.hpp"

#include "Components/MoveComponent.hpp"
#include "Components/AttackOrderComponent.hpp"
#include "Components/GarissonComponent.hpp"

#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"

namespace Systems {
        void CombatSystem(Game::GameEntityManager& manager, float dt) {

            std::unordered_set<EntityID> toRemove;

            // auto& entities = entityManager.getAllEntities();
            auto entities = manager.getAllEntityIDs();
        
            for (auto id : entities) {
                auto* attackOrder = manager.getComponent<Components::AttackOrderComponent>(id);
                auto* originGarisson = manager.getComponent<Components::GarissonComponent>(id);
                auto* drone = manager.getComponent<Components::DroneComponent>(id);
                auto* move = manager.getComponent<Components::MoveComponent>(id);

                if (attackOrder && originGarisson) {
                    // log_info << "Garisson has attack order";
                    // Attack order was just palced at a garison
                    // Create drones and send them to the target
                    if (originGarisson->getDroneCount() < 2) {
                        // log_info << "EntityID: " << id << " has no drones, removing attack order";
                        manager.removeComponent<Components::AttackOrderComponent>(id);
                        continue;
                    }

                    EntityID originEntity = attackOrder->origin;
                    EntityID targetEntity = attackOrder->target;

                    auto* originFaction = manager.getComponent<Components::FactionComponent>(originEntity);
                    auto* targetFaction = manager.getComponent<Components::FactionComponent>(targetEntity);

                    // TODO: insert error msg if originFaction is missing
                    auto dronesUsedForAttack = originGarisson->getDroneCount()-1;

                    for(auto i=0; i < dronesUsedForAttack; i++){
                        EntityID droneID = Game::createDrone(manager, std::to_string(i), originFaction->faction);

                        manager.addComponent<Components::AttackOrderComponent>(droneID,attackOrder->origin, attackOrder->target);

                        sf::Vector2f originPosition = manager.getComponent<Components::TransformComponent>(originEntity)->transform.getPosition();
                        int spread = 25 + (dronesUsedForAttack * 5);
                        spread = std::min(spread, 75);
                        sf::Vector2f randomOffset = sf::Vector2f(
                            rand() % (2 * spread) - spread,
                            rand() % (2 * spread) - spread
                        );

                        auto* droneTransform = manager.getComponent<Components::TransformComponent>(droneID);
                        droneTransform->transform.setPosition(originPosition + randomOffset);

                        auto* droneMove = manager.getComponent<Components::MoveComponent>(droneID);
                        droneMove->targetPosition = manager.getComponent<Components::TransformComponent>(targetEntity)->transform.getPosition();
                        droneMove->moveToTarget = true;
                    }
                    originGarisson->setDroneCount(1);
                    manager.removeComponent<Components::AttackOrderComponent>(id);
                }
                else if (attackOrder && drone && move) {
                    if (!move->moveToTarget) {
                        // Drone Reached destination

                        EntityID originEntity = attackOrder->origin;
                        EntityID targetEntity = attackOrder->target;
                        
                        auto* originFaction = manager.getComponent<Components::FactionComponent>(originEntity); // Get the faction of the drone, in case the origin entity changed factions
                        auto* targetFaction = manager.getComponent<Components::FactionComponent>(targetEntity);
                        auto* targetGarisson = manager.getComponent<Components::GarissonComponent>(targetEntity);
                        auto* targetShield = manager.getComponent<Components::ShieldComponent>(targetEntity);
        
                        if(!targetShield){
                            log_err << "EntityID: " << " has no shield, but has an attack order";
                        }

                        if (targetGarisson && originFaction && targetFaction) {
                            
                            // No matter what, drone entity needs to be removed
                            toRemove.insert(id);

                            auto* gameState = manager.getGameStateComponent();

                            if(originFaction->faction == targetFaction->faction){
                                // Same faction, park drones
                                targetGarisson->incrementDroneCount();
                                continue; 
                            }
                            
                            // If shield is positive, hit shield and update its value
                            if(targetShield->getShield() > 1.f){
                                targetShield->decrementShield();
                            }else{
                                targetShield->setShield(0.f); 
                            }
                            
                            if(targetShield->getShield() > 0.f){
                                // Shield was hit but still up, attacking player loses drones
                                gameState->playerDrones[originFaction->faction]--;

                            }else if(targetGarisson->getDroneCount() > 0){
                                // Shield is down
                                // Different faction has drones parked
                                // Kill drones
                                targetGarisson->decrementDroneCount();

                                // both players lose drones
                                gameState->playerDrones[originFaction->faction]--;
                                gameState->playerDrones[targetFaction->faction]--;
                            }else{
                                // Different Faction, no shield, no drones, switch factions
                                targetFaction->faction = originFaction->faction;
                                targetGarisson->incrementDroneCount();
                            }
                            
                        }
                    }
                }
            }

            for (const auto& id : toRemove) {
                manager.removeEntity(id);
            }
        }

}

#endif // COMBAT_SYSTEM_HPP