#ifndef AI_EXECUTE_SYSTEM_HPP
#define AI_EXECUTE_SYSTEM_HPP

#include "Game/GameEntityManager.hpp"

#include "Config.hpp"

namespace Systems::AI {

    void ExecuteSystem(Game::GameEntityManager& entityManager, float dt){
        Entity& aiEntity = entityManager.getAIEntity();
        auto* aiComp = aiEntity.getComponent<Components::AIComponent>();
    
        int attackOrdersExecuted = 0;

        for(auto& [source, target, cost] : aiComp->execute.finalTargets){
            // log_info << "Attack: "<< source << " -> " << target;
            entityManager.addComponent(source, Components::AttackOrderComponent{source, target});
            attackOrdersExecuted++;

            if (attackOrdersExecuted >= Config::AI_MAX_EXECUTIONS_PER_TURN) break;
        }
    }
}

#endif // AI_EXECUTE_SYSTEM_HPP