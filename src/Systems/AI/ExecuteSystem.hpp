#ifndef AI_EXECUTE_SYSTEM_HPP
#define AI_EXECUTE_SYSTEM_HPP

#include "Game/GameEntityManager.hpp"

#include "Config.hpp"

namespace Systems::AI {

    void ExecuteSystem(Game::GameEntityManager& entityManager, float dt){
        Entity& aiEntity = entityManager.getAIEntity();
        auto* aiComp = aiEntity.getComponent<Components::AIComponent>();
    
        unsigned int attackOrdersExecuted = 0;

        for(auto& [source, target, distance, cost] : aiComp->execute.finalTargets){
            // log_info << "Attack: "<< source << " -> " << target;
            entityManager.addComponent(source, Components::AttackOrderComponent{source, target});
            attackOrdersExecuted++;

            if(Config::ENABLE_DEBUG_SYMBOLS){
                auto* originTransform = entityManager.getEntity(source).getComponent<Components::TransformComponent>();
                auto* targetTransform = entityManager.getEntity(target).getComponent<Components::TransformComponent>();
                aiComp->debug.yellowDebugTargets.push_back(originTransform->getPosition());
                aiComp->debug.pinkDebugTargets.push_back(targetTransform->getPosition());
            }

            if (attackOrdersExecuted >= Config::Difficulty::AI_MAX_EXECUTIONS_PER_TURN) break;
        }
    }
}

#endif // AI_EXECUTE_SYSTEM_HPP