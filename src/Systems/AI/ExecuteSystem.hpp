#ifndef AI_EXECUTE_SYSTEM_HPP
#define AI_EXECUTE_SYSTEM_HPP

#include "Game/GameEntityManager.hpp"

#include "Config.hpp"

namespace Systems::AI {

    void ExecuteSystem(Game::GameEntityManager& manager, float dt){
        auto* aiComp = manager.getAIComponent();
    
        unsigned int attackOrdersExecuted = 0;

        for(auto& [source, target, distance, cost] : aiComp->execute.finalTargets){
            // log_info << "Attack: "<< source << " -> " << target;
            manager.addOrReplaceComponent<Components::AttackOrderComponent>(source, source, target);
            attackOrdersExecuted++;

            if(Config::ENABLE_DEBUG_SYMBOLS){
                auto* originTransform = manager.getComponent<Components::TransformComponent>(source);
                auto* targetTransform = manager.getComponent<Components::TransformComponent>(target);
                aiComp->debug.yellowDebugTargets.push_back(originTransform->getPosition());
                aiComp->debug.pinkDebugTargets.push_back(targetTransform->getPosition());
            }

            if (attackOrdersExecuted >= Config::Difficulty::AI_MAX_EXECUTIONS_PER_TURN) break;
        }
    }
}

#endif // AI_EXECUTE_SYSTEM_HPP