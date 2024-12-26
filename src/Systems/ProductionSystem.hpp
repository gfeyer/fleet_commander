#ifndef PRODUCTION_SYSTEM_HPP
#define PRODUCTION_SYSTEM_HPP

#include <unordered_map>
#include <sstream>
#include "Core/Entity.hpp"

#include "Components/FactoryComponent.hpp"
#include "Components/Builder.hpp"

#include "Utils/Logger.hpp"
#include "Config.hpp"

namespace Systems {

    void ProductionSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {
        for (auto& [id, entity] : entities) {
            auto* factory = entity.getComponent<Components::FactoryComponent>();
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();
            auto* text = entity.getComponent<Components::TextComponent>(); 

            if (factory && transform && faction && faction->factionID) {
                factory->productionTimer += dt;

                if (factory->productionTimer >= factory->droneProductionRate) {
                    factory->productionTimer = 0.f;
                    factory->stationedDrones++;
                }
            }

            if (factory &&text){
                std::stringstream ss;
                ss << factory->factoryName << "\nDrones: " << factory->stationedDrones << "";
                text->setText(ss.str());
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP