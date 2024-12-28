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
        for (auto& [id, entity] : entities) {

            auto* factory = entity.getComponent<Components::FactoryComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();
            auto* garisson = entity.getComponent<Components::GarissonComponent>(); 

            // Generate drones in factories
            if (factory && faction && faction->factionID && garisson) {
                factory->productionTimer += dt;

                // Timer still ongoing, skip
                if(factory->productionTimer < factory->droneProductionRate){
                    continue;
                }

                // Reset timer after full cycle
                factory->productionTimer = 0.f;

                // If no energy, do not generate new drones
                auto* gameState = entityManager.getGameStateEntity().getComponent<Components::GameStateComponent>();
                if(gameState->playerEnergy[faction->factionID] >= gameState->playerDrones[faction->factionID]){
                    continue;
                }
                
                // Add one drone to player
                garisson->incrementDroneCount();
                gameState->playerDrones[faction->factionID]++;
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP