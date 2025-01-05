#ifndef PRODUCTION_SYSTEM_HPP
#define PRODUCTION_SYSTEM_HPP

#include <unordered_map>
#include <sstream>


#include "Components/FactoryComponent.hpp"
#include "Game/Builder.hpp"

#include "Utils/Logger.hpp"
#include "Config.hpp"

namespace Systems {

    void ProductionSystem(Game::GameEntityManager& manager, float dt) {

        auto entities = manager.getAllEntityIDs();
        auto* gameState = manager.getGameStateComponent();

        // Update all energy totals
        gameState->ClearAllEnergy();
        for(auto id : entities){
            auto* powerPlant = manager.getComponent<Components::PowerPlantComponent>(id);
            auto* faction = manager.getComponent<Components::FactionComponent>(id);
            
            if(powerPlant && faction){
                gameState->playerEnergy[faction->faction] += powerPlant->capacity; 
            }
        }

        // Update all drone production
        for (auto id : entities) {

            auto* factory = manager.getComponent<Components::FactoryComponent>(id);
            auto* faction = manager.getComponent<Components::FactionComponent>(id);
            auto* garisson = manager.getComponent<Components::GarissonComponent>(id); 

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
                auto* gameState = manager.getGameStateComponent();
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