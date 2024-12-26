#ifndef COMBAT_SYSTEM_HPP
#define COMBAT_SYSTEM_HPP

#include <unordered_map>
#include <unordered_set>

#include "Core/Entity.hpp"

#include "Components/MoveComponent.hpp"
#include "Core/Entity.hpp"

#include "Utils/Logger.hpp"

namespace Systems {
        void CombatSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {

            std::unordered_set<EntityID> toRemove;

            for (auto& [id, entity] : entities) {
                auto* attackOrder = entity.getComponent<Components::AttackOrderComponent>();

                if (attackOrder) {
                    auto* droneTransform = entity.getComponent<Components::TransformComponent>();
                    auto* droneMove = entity.getComponent<Components::MoveComponent>();

                    auto* originTransform = entities[attackOrder->origin].getComponent<Components::TransformComponent>();
                    auto* targetTransform = entities[attackOrder->target].getComponent<Components::TransformComponent>();

                    if (!droneTransform || !droneMove || !originTransform || !targetTransform) {
                        continue;
                    }

                    if(!attackOrder->isActivated){
                        droneTransform->transform.setPosition(originTransform->transform.getPosition());
                        droneMove->targetPosition = targetTransform->transform.getPosition();
                        droneMove->moveToTarget = true;
                        attackOrder->isActivated = true;
                    }else if (!droneMove->moveToTarget) {
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