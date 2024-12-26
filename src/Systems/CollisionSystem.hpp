#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include <unordered_map>
#include "Core/Entity.hpp"

#include "Components/DroneComponent.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/OutpostComponent.hpp"

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
                for (auto& [id2, entity2] : entities) {
                    auto* factoryComp = entity2.getComponent<Components::FactoryComponent>();
                    auto* outpostComp = entity2.getComponent<Components::OutpostComponent>();

                    auto* shapeComp = entity2.getComponent<Components::ShapeComponent>();
                    auto* factionComp = entity2.getComponent<Components::FactionComponent>();

                    if(shapeComp){
                        if (factoryComp || outpostComp) {
                            if (droneShape->shape->getGlobalBounds().intersects(shapeComp->shape->getGlobalBounds())) {
                                // Drone collided with factory or outpost
                                if(droneFaction && factionComp && droneFaction->factionID != factionComp->factionID) {
                                    // Drone collided with a different faction's factory or outpost
                                    factionComp->factionID = droneFaction->factionID;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif