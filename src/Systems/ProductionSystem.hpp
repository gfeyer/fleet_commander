#ifndef PRODUCTION_SYSTEM_HPP
#define PRODUCTION_SYSTEM_HPP

#include <unordered_map>
#include "Core/Entity.hpp"

#include "Components/FactoryComponent.hpp"
#include "Components/Builder.hpp"

#include "Utils/Logger.hpp"

namespace Systems {

    void ProductionSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {
        for (auto& [id, entity] : entities) {
            auto* factory = entity.getComponent<Components::FactoryComponent>();
            auto* transform = entity.getComponent<Components::TransformComponent>();

            if (factory && transform) {
                factory->productionTimer += dt;

                if (factory->productionTimer >= factory->droneProductionRate) {
                    factory->productionTimer = 0.f;
                    auto drone = Builder::createDrone();

                    EntityID droneId = drone.id;
                    
                    entities.emplace(droneId, std::move(drone));

                    factory->drones.insert(droneId);

                    // Place drone around the factory
                    auto* droneTransform = entities.at(droneId).getComponent<Components::TransformComponent>();
                    if (droneTransform) {
                        sf::Vector2f offset(rand() % 30, rand() % 30);
                        droneTransform->transform.setPosition(transform->transform.getPosition() + offset);
                    }
                }
            }
        }
    }
}

#endif // PRODUCTION_SYSTEM_HPP