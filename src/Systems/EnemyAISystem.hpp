#ifndef ENEMY_AI_SYSTEM_HPP
#define ENEMY_AI_SYSTEM_HPP

#include <unordered_map>
#include <map>
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
            aiComponent->highlightedEntityID = 0;

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
            // log_info << "Wait Score: " << actionScores["Wait"];
            // log_info << "Attack Power Station Score: " << actionScores["AttackPowerStation"];
            // log_info << "Attack Factory Score: " << actionScores["AttackFactory"];

             // Choose the best action
            auto bestAction = std::max_element(
                actionScores.begin(),
                actionScores.end(),
                [](const auto& a, const auto& b) {
                    return a.second < b.second;
                }
            );

            if (bestAction != actionScores.end()) {
                // log_info << "AI Decision: " << bestAction->first << " score: " << bestAction->second << std::endl;
            }

            // Get all available drones and stations
            using defense = float;
            unsigned int totalDrones = 0;
            std::map<EntityID, unsigned int> availableDrones;
            std::map<EntityID, defense> availablePowerStations;
            std::map<EntityID, defense> availableFactories; 

            for (const auto& [id, entity] : entityManager.getAllEntities()) {
                auto* shieldComp = entity.getComponent<Components::ShieldComponent>();
                auto* droneComp = entity.getComponent<Components::DroneComponent>();
                auto* powerComp = entity.getComponent<Components::PowerPlantComponent>();
                auto* factoryComp = entity.getComponent<Components::FactoryComponent>();
                auto* factionComp = entity.getComponent<Components::FactionComponent>();
                auto* garissonComp = entity.getComponent<Components::GarissonComponent>();

                // compute available drones
                if(factionComp && factionComp->faction == Components::Faction::PLAYER_2 && garissonComp){
                    availableDrones[id] += garissonComp->getDroneCount();
                    totalDrones += garissonComp->getDroneCount();
                }

                // compute defenses for all remaining units
                if(shieldComp && garissonComp && factionComp && factionComp->faction != Components::Faction::PLAYER_2){
                    if(factoryComp){
                        availableFactories[id] += shieldComp->maxShield;
                        availableFactories[id] += garissonComp->getDroneCount();
                    }else if(powerComp){
                        availablePowerStations[id] += shieldComp->maxShield;
                        availablePowerStations[id] += garissonComp->getDroneCount();
                    }else{
                        log_err << "Weird component combination detected";
                    }
                }
            }

            // Reversed Maps
            std::multimap<defense, EntityID> availablePowerStationsByDefense;
            for(auto& [id, defense] : availablePowerStations){
                availablePowerStationsByDefense.emplace(defense, id);
            }
            std::multimap<defense, EntityID> availableFactoriesByDefense;
            for(auto& [id, defense] : availableFactories){
                availableFactoriesByDefense.emplace(defense, id);
            }

            log_info << "AI: total drones available: " << totalDrones;

            // Execute Action
            if (bestAction->first == "Wait") {
                // TODO: nothing
            }else if(bestAction->first == "AttackPowerStation"){
                // Get the best power station
                for(auto& [defense, id] : availablePowerStationsByDefense){
                    log_info << "Attacking Power Station " << id << " with " << defense << " defense" << std::endl;
                    aiComponent->highlightedEntityID = id;
                    break;
                }

            }else if(bestAction->first == "AttackFactory"){
                // Get the best factory
                for(auto& [defense, id] : availableFactoriesByDefense){
                    log_info << "Attacking Factory " << id << " with " << defense << " defense" << std::endl;
                    aiComponent->highlightedEntityID = id;
                    break;
                }
            }else{
                // do nothing
            }
        }

}

#endif // ENEMY_AI_SYSTEM_HPP