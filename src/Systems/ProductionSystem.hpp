#ifndef PRODUCTION_SYSTEM_HPP
#define PRODUCTION_SYSTEM_HPP

#include <unordered_map>
#include "Core/Entity.hpp"

#include "Components/FactoryComponent.hpp"

#include "Utils/Logger.hpp"

namespace Systems {

    void ProductionSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {
        for (auto& [id, entity] : entities) {
            auto* factory = entity.getComponent<Components::FactoryComponent>();

            if (factory) {
                factory->productionTimer += dt;

                if (factory->productionTimer >= factory->droneProductionRate) {
                    factory->productionTimer = 0.f;
                    // TODO: create and add drone here
                    log_info << "creating drone";
                }
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP