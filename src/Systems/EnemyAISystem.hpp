#ifndef ENEMY_AI_SYSTEM_HPP
#define ENEMY_AI_SYSTEM_HPP

#include <unordered_map>
#include <map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <algorithm>


#include "Game/GameEntityManager.hpp"

namespace Systems {
        void EnemyAISystem(Game::GameEntityManager& entityManager, float dt) {

            static float decisionTimer = 0.f;
            static float decisionTimerMax = 1.f; 
            
            // Execute every 1 second
            decisionTimer += dt;
            if (decisionTimer <= decisionTimerMax) {
                return;
            }
            decisionTimer = 0.f;

            Entity& aiEntity = entityManager.getEnemyAIEntity();
            auto* aiComponent = aiEntity.getComponent<Components::AIComponent>();

            if(!aiComponent){
                log_err << "Failed to get aiComponent" << std::endl;
                return;
            }


            return;
            // --------------------------------------------------------------------
            // Old logic
            // -------------------------------------------------------------------
            

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
            sf::Vector2f aiCentralPosition = {0.f, 0.f};
            std::unordered_set<EntityID> entitiesWhereDronesAreStationed;

            for (const auto& [id, entity] : entityManager.getAllEntities()) {
                auto* shieldComp = entity.getComponent<Components::ShieldComponent>();
                auto* droneComp = entity.getComponent<Components::DroneComponent>();
                auto* powerComp = entity.getComponent<Components::PowerPlantComponent>();
                auto* factoryComp = entity.getComponent<Components::FactoryComponent>();
                auto* factionComp = entity.getComponent<Components::FactionComponent>();
                auto* garissonComp = entity.getComponent<Components::GarissonComponent>();

                std::vector<sf::Vector2f> aiBuildingPositions;
                
                // compute available drones & central AI position on map
                if(factionComp && factionComp->faction == Components::Faction::PLAYER_2 && garissonComp){

                    unsigned int droneCount = garissonComp->getDroneCount();
                    availableDrones[id] += droneCount;
                    totalDrones += droneCount;
                    auto* transform = entity.getComponent<Components::TransformComponent>();
                    if(transform){
                        aiBuildingPositions.push_back(transform->getPosition());
                    }

                    if (droneCount > 0) {
                        entitiesWhereDronesAreStationed.insert(id);
                    }
                }

                for(auto& pos : aiBuildingPositions){
                    aiCentralPosition.x += pos.x;
                    aiCentralPosition.y += pos.y;
                }
                aiCentralPosition.x /= aiBuildingPositions.size();
                aiCentralPosition.y /= aiBuildingPositions.size();

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

            // Reversed Maps so we have defense -> id
            std::multimap<defense, EntityID> availablePowerStationsByDefense;
            for(auto& [id, defense] : availablePowerStations){
                availablePowerStationsByDefense.emplace(defense, id);
            }
            std::multimap<defense, EntityID> availableFactoriesByDefense;
            for(auto& [id, defense] : availableFactories){
                availableFactoriesByDefense.emplace(defense, id);
            }

            // log_info << "AI: total drones available: " << totalDrones;

            // Execute Action
            if (bestAction->first == "Wait") {
                // TODO: nothing
            }else if(bestAction->first == "AttackPowerStation"){
                // Get the best power station
                
                // Get eligible IDs where we have enough drones to attack
                std::unordered_set<EntityID> selectedPowerStations;
                for(auto& [defense, id] : availablePowerStationsByDefense){
                    if(totalDrones > defense+2){
                        selectedPowerStations.insert(id);
                    }else{
                        break;
                    }
                }

                // select closest target
                if(selectedPowerStations.size() > 0){
                    
                    std::map<float, EntityID> selectedPowerStationsByDistance;
                    for(auto& id : selectedPowerStations){
                        auto* transform = entityManager.getEntity(id).getComponent<Components::TransformComponent>();
                        if(transform){
                            float distance = sqrt(pow(transform->getPosition().x - aiCentralPosition.x, 2) + pow(transform->getPosition().y - aiCentralPosition.y, 2));
                            selectedPowerStationsByDistance.emplace(distance, id);
                        }
                    }
                    
                    EntityID selectedTargetID = selectedPowerStationsByDistance.begin()->second;
                    // log_info << "Attacking Power Station " << selectedTargetID;
                    aiComponent->highlightedEntityID = selectedTargetID;

                    // Add attack orders
                    for(auto id : entitiesWhereDronesAreStationed){
                        entityManager.addComponent(id, Components::AttackOrderComponent{id, selectedTargetID});
                    }

                }else{
                    // log_info << "Not enoug drones for attack";
                }

            }else if(bestAction->first == "AttackFactory"){
                // Get the best factory
                
                // Get eligible IDs where we have enough drones to attack
                std::unordered_set<EntityID> selectedFactories;
                for(auto& [defense, id] : availableFactoriesByDefense){
                    if(totalDrones > defense+2){
                        selectedFactories.insert(id);
                    }else{
                        break;
                    }
                }

                // select closest target
                if(selectedFactories.size() > 0){
                    
                    std::map<float, EntityID> selectedFactoriesByDistance;
                    for(auto& id : selectedFactories){
                        auto* transform = entityManager.getEntity(id).getComponent<Components::TransformComponent>();
                        if(transform){
                            float distance = sqrt(pow(transform->getPosition().x - aiCentralPosition.x, 2) + pow(transform->getPosition().y - aiCentralPosition.y, 2));
                            selectedFactoriesByDistance.emplace(distance, id);
                        }
                    }
                    
                    EntityID selectedTargetID = selectedFactoriesByDistance.begin()->second;
                    // log_info << "Attacking Factory " << selectedTargetID;
                    aiComponent->highlightedEntityID = selectedTargetID;

                    // Add attack orders
                    for(auto id : entitiesWhereDronesAreStationed){
                        entityManager.addComponent(id, Components::AttackOrderComponent{id, selectedTargetID});
                    }

                }else{
                    // log_info << "Not enough drones for attack";
                }
            }else{
                // do nothing
            }
        }

}

#endif // ENEMY_AI_SYSTEM_HPP