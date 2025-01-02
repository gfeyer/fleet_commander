#ifndef DRONE_TRANSFER_SYSTEM_HPP
#define DRONE_TRANSFER_SYSTEM_HPP    

#include "Game/GameEntityManager.hpp"

#include "Components/DroneTransferComponent.hpp"

namespace Systems {

    void DroneTransferSystem(Game::GameEntityManager& entityManager, float dt) {

        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {

            auto* droneTransferComp = entity.getComponent<Components::DroneTransferComponent>();

            if (droneTransferComp) {
                // Check if faction is the same
                auto* factionComp = entity.getComponent<Components::FactionComponent>();
                if(factionComp && factionComp->faction != droneTransferComp->faction){
                    entityManager.removeComponent<Components::DroneTransferComponent>(id);
                    continue;
                }

                // Check if there's any drones to transfer
                auto* garissonComp = entity.getComponent<Components::GarissonComponent>();
                if(garissonComp && garissonComp->getDroneCount() > 0){
                    auto source = droneTransferComp->source;
                    auto target = droneTransferComp->target;
                    entityManager.addComponent(source, Components::AttackOrderComponent{source, target});
                }

                // Update Animation dot 
                /*
                auto* sourceTransform = entityManager.getComponent<Components::TransformComponent>(droneTransferComp->source);
                auto* targetTransform = entityManager.getComponent<Components::TransformComponent>(droneTransferComp->target);

                if (sourceTransform && targetTransform) {
                    sf::Vector2f start = sourceTransform->getPosition();
                    sf::Vector2f end = targetTransform->getPosition();

                    sf::Vector2f direction = end - start;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length; // Normalize

                    // Update animation progress
                    droneTransferComp->currentDistance += droneTransferComp->speed * dt;
                    if (droneTransferComp->currentDistance > length) {
                        droneTransferComp->currentDistance = 0.f; // Reset animation
                    }

                    // Calculate dot position
                    droneTransferComp->dotPosition = start + direction * droneTransferComp->currentDistance;
                }*/
            }
        }
    }
}

#endif // DRONE_TRANSFER_SYSTEM_HPP