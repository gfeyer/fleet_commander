#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <unordered_map>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/MoveComponent.hpp"
#include "Config.hpp"

namespace Systems {
    void MovementSystem(std::unordered_map<int, Entity>& entities, float dt) {
        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* move = entity.getComponent<Components::MoveComponent>();

            if (transform && move) {
                // Update position based on velocity
                sf::Vector2f newPosition = transform->getPosition() + move->velocity * dt;
                transform->transform.setPosition(newPosition);

                if (move->velocity.x != 0.f || move->velocity.y != 0.f) {
                    float angle = std::atan2(move->velocity.y, move->velocity.x) * Config::RAD_TO_DEG;
                    transform->transform.setRotation(angle + 90.f); // +90 to align triangle tip upwards
                }

                // Update rotation based on angular velocity
                float newRotation = transform->getRotation() + move->angularVelocity * dt;
                transform->transform.setRotation(newRotation);
            }
        }
    }
}

#endif // MOVEMENT_SYSTEM_HPP