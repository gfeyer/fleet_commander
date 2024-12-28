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
        void CombatSystem(Game::GameEntityManager& entityManager, float dt) {

            std::unordered_set<EntityID> toRemove;

            // Get all entities by IDs
            const auto& entityIDs = entityManager.getAllEntityIDs();

            for (EntityID id : entityIDs) {
                Entity& entity = entityManager.getEntity(id); // Access entity by ID
                auto* attackOrder = entityManager.getComponent<Components::AttackOrderComponent>(id);
                auto* garisson = entity.getComponent<Components::GarissonComponent>();
                auto* drone = entity.getComponent<Components::DroneComponent>();
                auto* move = entity.getComponent<Components::MoveComponent>();

                if (attackOrder && garisson) {
                    // log_info << "Garisson has attack order";
                    // Attack order was just palced at a garison
                    // Create drones and send them to the target
                    if (garisson->getDroneCount() < 2) {
                        log_info << "EntityID: " << id << " has no drones, removing attack order";
                        entity.removeComponent<Components::AttackOrderComponent>();
                        entityManager.removeComponent<Components::AttackOrderComponent>(id);
                        continue;
                    }

                    auto* originFaction = entityManager.getEntity(attackOrder->origin).getComponent<Components::FactionComponent>();

                    // TODO: insert error msg if originFaction is missing
                    auto dronesUsedForAttack = garisson->getDroneCount()-1;

                    for(auto i=0; i < dronesUsedForAttack; i++){
                        EntityID droneID = Game::createDrone(entityManager, std::to_string(i), originFaction->factionID);
                        entityManager.addComponent(droneID, Components::AttackOrderComponent{attackOrder->origin, attackOrder->target});
                        auto* transform = entityManager.getComponent<Components::TransformComponent>(droneID);
                        sf::Vector2f startPosition = entityManager.getComponent<Components::TransformComponent>(attackOrder->origin)->transform.getPosition();
                        int spread = 25 + (dronesUsedForAttack * 5);
                        spread = std::min(spread, 75);
                        sf::Vector2f randomOffset = sf::Vector2f(
                            rand() % (2 * spread) - spread,
                            rand() % (2 * spread) - spread
                        );
                        transform->transform.setPosition(startPosition + randomOffset);

                        auto* move = entityManager.getComponent<Components::MoveComponent>(droneID);
                        move->targetPosition = entityManager.getComponent<Components::TransformComponent>(attackOrder->target)->transform.getPosition();
                        move->moveToTarget = true;
                    }
                    garisson->setDroneCount(1);
                    entity.removeComponent<Components::AttackOrderComponent>();
                }
                else if (attackOrder && drone && move) {
                    if (!move->moveToTarget) {
                        log_info << "Drone " << id << " has reached target";
                        // Reached destination
                        auto* targetGarisson = entityManager.getComponent<Components::GarissonComponent>(attackOrder->target);
                        auto* originFaction = entityManager.getComponent<Components::FactionComponent>(attackOrder->origin);
                        auto* targetFaction = entityManager.getComponent<Components::FactionComponent>(attackOrder->target);
                        auto* targetShield = entityManager.getComponent<Components::ShieldComponent>(attackOrder->target);

                        unsigned int targetShieldValue = 0;
                        if(targetShield){
                            targetShieldValue = targetShield->getShield();
                        }

                        if (targetGarisson && originFaction && targetFaction) {

                            if(originFaction->factionID == targetFaction->factionID){
                                // Same faction, park drones
                                targetGarisson->incrementDroneCount();
                            }else if(targetShieldValue > 0){
                                // Different faction, damage shield
                                targetShield->decrementShield();
                            }else if(targetGarisson->getDroneCount() > 0){
                                // Different faction, shield down, kill parked drones
                                targetGarisson->decrementDroneCount();
                            }else{
                                // Different Faction, no shield, no drones, switch factions
                                targetFaction->factionID = originFaction->factionID;
                                targetGarisson->incrementDroneCount();
                            }

                            toRemove.insert(id);
                        }
                    }
                }
            }

            for (const auto& id : toRemove) {
                entityManager.removeEntity(id);
            }
        }

}

#endif // COMBAT_SYSTEM_HPP