#ifndef ENEMY_AI_SYSTEM_HPP
#define ENEMY_AI_SYSTEM_HPP

#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>


#include "Game/GameEntityManager.hpp"

namespace Systems {
        void EnemyAISystem(Game::GameEntityManager& entityManager, float dt) {
            Entity& aiEntity = entityManager.getEnemyAIEntity();
            auto* aiComponent = aiEntity.getComponent<Components::EnemyAIComponent>();

            if(!aiComponent){
                log_err << "Failed to get aiComponent" << std::endl;
                return;
            }

            aiComponent->decisionTimer += dt;
            if (aiComponent->decisionTimer <= aiComponent->decisionTimerMax) {
                return;
            }

            aiComponent->decisionTimer = 0.f;

             // Get Game State
            auto* gameStateComponent = entityManager.getGameStateEntity().getComponent<Components::GameStateComponent>();
            if (!gameStateComponent) {
                log_err << "Failed to get gameStateComponent" << std::endl;
                return;
            }

            auto drones = gameStateComponent->playerDrones[Components::Faction::PLAYER_2];
            auto energy = gameStateComponent->playerEnergy[Components::Faction::PLAYER_2];

            // Calculate action scores
            std::unordered_map<std::string, float> actionScores;

            // Ensure no division by zero
            float maxResources = std::max(std::max(float(drones), float(energy)), 1.0f);

            // Wait Score
            // TODO
            // actionScores["Wait"] =  (std::abs(float(drones - energy)) / maxResources);

            // Attack Power Station Score
            if (energy < 20.0f) {
                actionScores["AttackPowerStation"] = 1.0f; // Highest priority if energy is critically low
            } else {
                actionScores["AttackPowerStation"] = 1.0f - (float(energy) / std::max(float(drones), 1.0f));
            }

            // Attack Factory Score
            if (drones < energy / 2.0f) {
                actionScores["AttackFactory"] = 1.0f; // Highest priority if drones are significantly less than energy
            } else {
                actionScores["AttackFactory"] = 1.0f - (float(drones) / std::max(float(energy), 1.0f));
            }

            // Debug log the scores
            log_info << "Wait Score: " << actionScores["Wait"];
            log_info << "Attack Power Station Score: " << actionScores["AttackPowerStation"];
            log_info << "Attack Factory Score: " << actionScores["AttackFactory"];

             // Choose the best action
            auto bestAction = std::max_element(
                actionScores.begin(),
                actionScores.end(),
                [](const auto& a, const auto& b) {
                    return a.second < b.second;
                }
            );

            if (bestAction != actionScores.end()) {
                log_info << "AI Decision: " << bestAction->first << std::endl;
            }

            // Execute Action
            if (bestAction->first == "Wait") {
            }else if(bestAction->first == "AttackPowerStation"){
                
            }else if(bestAction->first == "AttackFactory"){
                
            }else{
                // do nothing
            }
        }

}

#endif // ENEMY_AI_SYSTEM_HPP