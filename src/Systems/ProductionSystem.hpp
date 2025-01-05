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
        
        // Update all energy totals
        auto* gameState = manager.getGameStateComponent();
        gameState->ClearAllEnergy();

        for(auto&& [id, powerPlant, faction] : manager.view<Components::PowerPlantComponent, Components::FactionComponent>().each()){
            gameState->playerEnergy[faction.faction] += powerPlant.capacity; 
        }

        // Update all drone production
        for (auto&& [id, factory, garisson, faction] : manager.view<Components::FactoryComponent, Components::GarissonComponent, Components::FactionComponent>().each()) {

            // Generate drones in factories
            if (faction.faction != Components::Faction::NEUTRAL) {
                // Accumulate production based on productionRate and dt
                factory.productionTimer += factory.droneProductionRate * dt;

                // Timer still ongoing, skip
                if(factory.productionTimer < 1.f){
                    continue;
                }

                // Reset timer after full cycle
                factory.productionTimer -= 1.f;

                // If less energy than drones, do not generate new drones
                auto* gameState = manager.getGameStateComponent();
                if(gameState->playerEnergy[faction.faction] <= gameState->playerDrones[faction.faction]){
                    continue;
                }
                
                // Add one drone to player
                garisson.incrementDroneCount();
                gameState->playerDrones[faction.faction]++;
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP