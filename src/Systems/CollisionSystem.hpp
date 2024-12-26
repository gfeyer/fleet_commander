#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include <unordered_map>
#include "Core/Entity.hpp"

#include "Components/DroneComponent.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/ShapeComponent.hpp"

namespace Systems {
    void CollisionSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {
        // Check every entity against another entity if it's collided

        for (auto& [id, entity] : entities) {
            // Check if a Drone collided with a Factory or Outpost
            auto* droneComp = entity.getComponent<Components::DroneComponent>();
            auto* droneShape = entity.getComponent<Components::ShapeComponent>();
            auto* droneFaction = entity.getComponent<Components::FactionComponent>();

            if (droneComp && droneShape) {
                // Check if the drone is colliding with a factory or outpost
                for (auto& [factoryId, factory] : entities) {
                    auto* factoryComp = factory.getComponent<Components::FactoryComponent>();
                    auto* factoryShape = factory.getComponent<Components::ShapeComponent>();
                    auto* factoryFaction = factory.getComponent<Components::FactionComponent>();

                    if (factoryComp && factoryShape) {
                        if (droneShape->shape->getGlobalBounds().intersects(factoryShape->shape->getGlobalBounds())) {
                            // Drone collided with factory or outpost
                            if(droneFaction && factoryFaction && droneFaction->factionID != factoryFaction->factionID) {
                                // Drone collided with a different faction's factory or outpost
                                factoryFaction->factionID = droneFaction->factionID;
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif