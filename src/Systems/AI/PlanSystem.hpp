#ifndef AI_PLAN_SYSTEM_HPP
#define AI_PLAN_SYSTEM_HPP

#include "Game/GameEntityManager.hpp"

#include "Utils/Logger.hpp"
#include "Config.hpp"

namespace Systems::AI {

    float computeAttackCost(Game::GameEntityManager& entityManager, EntityID targetEntityID, float distance) {
        // returns how many drones it would take to conquer the target

        auto* targetGarisson = entityManager.getEntity(targetEntityID).getComponent<Components::GarissonComponent>();
        auto* targetShield = entityManager.getEntity(targetEntityID).getComponent<Components::ShieldComponent>();

        // compute drone cost
        auto droneCost = targetGarisson->getDroneCount();
        
        // compute shield cost
        auto currentShield = targetShield->currentShield;

        // compute shield regen cost (for drone travel time)
        auto timeToReachTarget = distance / Config::DRONE_SPEED;
        auto shieldRegenRate = targetShield->regenRate;
        auto shieldRegenCost = timeToReachTarget * shieldRegenRate;

        return droneCost + currentShield + shieldRegenCost;
    }

    void PlanSystem(Game::GameEntityManager& entityManager, float dt){
        Entity& aiEntity = entityManager.getAIEntity();
        auto* aiComp = aiEntity.getComponent<Components::AIComponent>();

        if(!aiComp){
            log_err << "Failed to get aiComponent";
        }

        // Reset last plan
        aiComp->plan.reset();

        // Plan: Check if any single garisson can conquer an adjacent target
        for(auto it = aiComp->perception.garissonsByDistance.begin(); it != aiComp->perception.garissonsByDistance.end(); it++){
            auto originGarissonID = it->first;
            auto distance = it->second.begin()->first;
            auto targetEntityID = it->second.begin()->second;

            float costForSuccesfulAttack = computeAttackCost(entityManager, targetEntityID, distance);
            auto droneCountAtThisGarisson = aiComp->perception.garissonByDroneCount.at(originGarissonID);

            if(droneCountAtThisGarisson > costForSuccesfulAttack){
                log_info << "Can conquer " << targetEntityID << " from " << originGarissonID;

                auto* originTransform = entityManager.getEntity(originGarissonID).getComponent<Components::TransformComponent>();
                auto* targetTransform = entityManager.getEntity(targetEntityID).getComponent<Components::TransformComponent>();
                aiComp->debug.yellowDebugTargets.push_back(originTransform->getPosition());
                aiComp->debug.pinkDebugTargets.push_back(targetTransform->getPosition());

                aiComp->plan.potentialAttackTargets[originGarissonID] = targetEntityID;
            }
        }
        

        // Plan: If no garisson alone can conquer adjacent targets, compute collective plan
        if(aiComp->plan.potentialAttackTargets.empty()){
            log_info << "No garisson alone can conquer adjacent targets, computing collective plan";
        }

    }
}

#endif // AI_PLAN_SYSTEM_HPP