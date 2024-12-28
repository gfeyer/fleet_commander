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

            // Get components            
            auto* factory = entity.getComponent<Components::FactoryComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();
            auto* garisson = entity.getComponent<Components::GarissonComponent>(); 

            if (factory && faction && faction->factionID && garisson) {
                factory->productionTimer += dt;

                if (factory->productionTimer >= factory->droneProductionRate) {
                    factory->productionTimer = 0.f;
                    garisson->incrementDroneCount();

                    // Update game state
                    auto* gameStateComp = entityManager.getGameStateEntity().getComponent<Components::GameStateComponent>();
                    if (gameStateComp) {
                        gameStateComp->playerDrones[faction->factionID]++;

                        log_info << "Player " << faction->factionID << " has " << gameStateComp->playerDrones[faction->factionID] << " drones";
                    }
                }
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP