#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <unordered_map>
#include <cmath>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/MoveComponent.hpp"
#include "Config.hpp"
#include "Utils/Logger.hpp"

namespace Systems {
    void MovementSystem(Game::GameEntityManager& entityManager, float dt) {

        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* move = entity.getComponent<Components::MoveComponent>();
            auto* tag = entity.getComponent<Components::TagComponent>();

            if (transform && move) {
                // Handle movement towards target
                if (move->moveToTarget) {
                    sf::Vector2f direction = move->targetPosition - transform->getPosition();
                    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                    float stoppingDistance = std::max(5.0f, move->speed * 0.1f); // 10% of speed, min 5 pixels
                    if (distance > stoppingDistance) { // Stop if close enough

                        direction /= distance; // Normalize direction vector

                        // Move towards the target
                        float step = move->speed * dt;

                        // Prevent overshooting by clamping step
                        if (step >= distance) {
                            transform->transform.setPosition(move->targetPosition);
                            move->moveToTarget = false; // Stop movement
                        } else {
                            sf::Vector2f newPosition = transform->getPosition() + direction * step;
                            transform->transform.setPosition(newPosition);

                            // Rotate towards target
                            float angle = std::atan2(direction.y, direction.x) * Config::RAD_TO_DEG;
                            transform->transform.setRotation(angle + 90.f); // Align triangle tip
                        }
                    } else {
                        // Snap to target when very close
                        transform->transform.setPosition(move->targetPosition);
                        move->moveToTarget = false; // Stop movement
                    }
                }

                // Handle angular rotation
                float newRotation = transform->getRotation() + move->angularVelocity * dt;
                transform->transform.setRotation(newRotation);
            }
        }
    }
}




#endif // MOVEMENT_SYSTEM_HPP