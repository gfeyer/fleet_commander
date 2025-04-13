#ifndef COMBAT_SYSTEM_HPP
#define COMBAT_SYSTEM_HPP

#include <unordered_map>
#include <unordered_set>

#include "Game/Builder.hpp"
#include "Components/MoveComponent.hpp"
#include "Components/AttackOrderComponent.hpp"
#include "Components/GarissonComponent.hpp"

#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"
#include "Utils/Random.hpp"

namespace Systems {
        void CombatSystem(Game::GameEntityManager& manager, float dt) {

            std::vector<EntityID> toRemoveEntities;
            std::vector<sf::Vector2f> toAddExplosionsAtPositions;

            for(auto&& [id, attackOrder, originGarisson, faction] : manager.view<
                Components::AttackOrderComponent, 
                Components::GarissonComponent,
                Components::FactionComponent>().each()){
                
                if(attackOrder.isActivated == false){
                    continue;
                }
                
                if(attackOrder.origin != id){
                    // log_err << "AttackOrder origin ID does not match current entity ID, skipping...";
                    continue;
                }

                if (originGarisson.getDroneCount() < 2) {
                    // log_info << "EntityID has no drones, removing attack order";
                    attackOrder.isActivated = false;
                    continue;
                }

                EntityID targetEntityID = attackOrder.target;

                auto dronesUsedForAttack = originGarisson.getDroneCount() - 1;

                for(auto i=0; i < dronesUsedForAttack; i++){
                    // Creating drones
                    EntityID droneID = Game::createDrone(manager, std::to_string(i), faction.faction);
                    manager.addOrReplaceComponent<Components::AttackOrderComponent>(droneID, attackOrder.origin, attackOrder.target);

                        sf::Vector2f originPosition = manager.getComponent<Components::TransformComponent>(id)->transform.getPosition();
                        int spread = 25 + (dronesUsedForAttack * 5);
                        spread = std::min(spread, 75);
                        sf::Vector2f randomOffset = sf::Vector2f(
                            rand() % (2 * spread) - spread,
                            rand() % (2 * spread) - spread
                        );

                        auto* droneTransform = manager.getComponent<Components::TransformComponent>(droneID);
                        droneTransform->transform.setPosition(originPosition + randomOffset);

                        auto* droneMove = manager.getComponent<Components::MoveComponent>(droneID);
                        droneMove->targetPosition = manager.getComponent<Components::TransformComponent>(targetEntityID)->transform.getPosition();
                        droneMove->moveToTarget = true;
                }
                originGarisson.setDroneCount(1);
                attackOrder.isActivated = false;
            }

            for(auto&& [id, drone, faction, attackOrder, move] : manager.view<
                Components::DroneComponent, 
                Components::FactionComponent,
                Components::AttackOrderComponent,
                Components::MoveComponent>().each()){                    
                
                if(move.moveToTarget == false){
                    // Drone Reached destination

                    EntityID originEntity = attackOrder.origin;
                    EntityID targetEntity = attackOrder.target;
                        
                    auto* targetFaction = manager.getComponent<Components::FactionComponent>(targetEntity);
                    auto* targetGarisson = manager.getComponent<Components::GarissonComponent>(targetEntity);
                    auto* targetShield = manager.getComponent<Components::ShieldComponent>(targetEntity);
        
                    if(!targetShield){
                        log_err << "target entity has no shield component which is required to be attacked";
                    }

                    if (targetGarisson && targetFaction) {

                        auto attackingFaction = faction.faction;
                        auto defendingFaction = targetFaction->faction;

                        // No matter what, drone entity needs to be removed
                        toRemoveEntities.push_back(id);

                        auto* gameState = manager.getGameStateComponent();

                        if(attackingFaction == defendingFaction){
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
                            gameState->playerDrones[attackingFaction]--;

                        }else if(targetGarisson->getDroneCount() > 0){
                            // Shield is down
                            // Different faction has drones parked
                            // Kill drones
                            targetGarisson->decrementDroneCount();

                            // both players lose drones
                            gameState->playerDrones[attackingFaction]--;
                            gameState->playerDrones[defendingFaction]--;
                        }else{
                            // Different Faction, no shield, no drones, switch factions
                            targetFaction->faction = attackingFaction;
                            targetGarisson->incrementDroneCount();
                        }

                        toAddExplosionsAtPositions.push_back(move.targetPosition);
                    }
                }
            }
            
            for(auto& position : toAddExplosionsAtPositions){
                position.x += Utils::getRandomFloat(-128.f, 128.f);
                position.y += Utils::getRandomFloat(-128.f, 128.f);
                Game::createExplosionAnimation(manager, position);
            }
  
            for (auto id : toRemoveEntities) {
                manager.removeEntity(id);
            }
        }
}

#endif // COMBAT_SYSTEM_HPP