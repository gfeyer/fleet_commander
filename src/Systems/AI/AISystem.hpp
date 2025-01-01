#ifndef AI_SYSTEM_HPP
#define AI_SYSTEM_HPP

#include <unordered_map>
#include <map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <algorithm>


#include "Game/GameEntityManager.hpp"
#include "Systems/AI/ExecuteSystem.hpp"
#include "Systems/AI/PlanSystem.hpp"
#include "Systems/AI/PerceptionSystem.hpp"

#include "Config.hpp"

namespace Systems::AI {
        void AISystem(Game::GameEntityManager& entityManager, float dt) {

            // Run AI every few seconds
            static float decisionTimer = 0.f;

            decisionTimer += dt;
            if(decisionTimer < Config::AI_DECISION_INTERVAL){
                return;
            }
            decisionTimer = 0.f;

            // Reset last plan
            Entity& aiEntity = entityManager.getAIEntity();
            auto* aiComponent = aiEntity.getComponent<Components::AIComponent>();
            aiComponent->reset();

            // Run AI
            Systems::AI::PerceptionSystem(entityManager, dt);
            Systems::AI::PlanSystem(entityManager, dt);
            Systems::AI::ExecuteSystem(entityManager, dt);

            return;
        }

}

#endif // AI_SYSTEM_HPP