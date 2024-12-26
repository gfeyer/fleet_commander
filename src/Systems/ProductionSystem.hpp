#ifndef PRODUCTION_SYSTEM_HPP
#define PRODUCTION_SYSTEM_HPP

#include <unordered_map>
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

            if (factory && transform && faction && faction->factionID) {
                factory->productionTimer += dt;

                if (factory->productionTimer >= factory->droneProductionRate) {
                    factory->productionTimer = 0.f;
                    auto drone = Builder::createDrone("", faction->factionID);

                    EntityID droneId = drone.id;
                    
                    entities.emplace(droneId, std::move(drone));

                    factory->drones.insert(droneId);

                    // Place drone around the factory
                    auto* droneTransform = entities.at(droneId).getComponent<Components::TransformComponent>();
                    if (droneTransform) {
                        sf::Vector2f offset(Config::FACTORY_SIZE + rand() % 100 - 50, Config::FACTORY_SIZE + rand() % 50);
                        droneTransform->transform.setPosition(transform->transform.getPosition() + offset);
                    }
                }
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP