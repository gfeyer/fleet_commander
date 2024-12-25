#ifndef MOVE_COMPONENT_HPP
#define MOVE_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components {
    struct MoveComponent {
        float speed;
        float angularVelocity; // Rotation speed (degrees per second)
        sf::Vector2f targetPosition; // Optional target position
        bool moveToTarget = false;   // Flag to enable movement to target

        MoveComponent() = default;

        MoveComponent(float speed, float angularVelocity)
            : speed(speed), angularVelocity(angularVelocity), moveToTarget(false) {}

        MoveComponent(float speed, float angularVelocity, const sf::Vector2f& target)
            : speed(speed), angularVelocity(angularVelocity), targetPosition(target), moveToTarget(true) {}    
    };
}

#endif // MOVE_COMPONENT_HPP