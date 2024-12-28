#ifndef PRODUCTION_SYSTEM_HPP
#define PRODUCTION_SYSTEM_HPP

#include <unordered_map>
#include <sstream>
#include "Core/Entity.hpp"

#include "Components/FactoryComponent.hpp"
#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"
#include "Config.hpp"

namespace Systems {

    void ProductionSystem(Game::GameEntityManager& entityManager, float dt) {

        auto& entities = entityManager.getAllEntities();
        auto* gameState = entityManager.getGameStateEntity().getComponent<Components::GameStateComponent>();

        // Update all energy totals
        gameState->ClearAllEnergy();
        for(auto& [id, entity] : entities){
            auto* powerPlant = entity.getComponent<Components::PowerPlantComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();
            
            if(powerPlant && faction){
                gameState->playerEnergy[faction->faction] += powerPlant->capacity; 
            }
        }

        // Update all drone production
        for (auto& [id, entity] : entities) {

            auto* factory = entity.getComponent<Components::FactoryComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();
            auto* garisson = entity.getComponent<Components::GarissonComponent>(); 

            // Generate drones in factories
            if (factory && garisson && faction && faction->faction != Components::Faction::NEUTRAL) {
                // Accumulate production based on productionRate and dt
                factory->productionTimer += factory->droneProductionRate * dt;

                // Timer still ongoing, skip
                if(factory->productionTimer < 1.f){
                    continue;
                }

                // Reset timer after full cycle
                factory->productionTimer -= 1.f;

                // If less energy than drones, do not generate new drones
                auto* gameState = entityManager.getGameStateEntity().getComponent<Components::GameStateComponent>();
                if(gameState->playerEnergy[faction->faction] <= gameState->playerDrones[faction->faction]){
                    continue;
                }
                
                // Add one drone to player
                garisson->incrementDroneCount();
                gameState->playerDrones[faction->faction]++;
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP