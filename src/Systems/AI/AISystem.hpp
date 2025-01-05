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
        void AISystem(Game::GameEntityManager& manager, float dt) {

            // Run AI every few seconds
            static float decisionTimer = 0.f;

            decisionTimer += dt;
            if(decisionTimer < Config::Difficulty::AI_DECISION_INTERVAL_SEC) {
                return;
            }
            decisionTimer = 0.f;

            // Reset last plan
            auto* aiComponent = manager.getAIComponent();
            aiComponent->reset();

            // Run AI
            Systems::AI::PerceptionSystem(manager, dt);
            Systems::AI::PlanSystem(manager, dt);
            Systems::AI::ExecuteSystem(manager, dt);

            return;
        }

}

#endif // AI_SYSTEM_HPP