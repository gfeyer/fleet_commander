#ifndef MOVE_COMPONENT_HPP
#define MOVE_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components {
    struct MoveComponent {
        sf::Vector2f velocity; // Speed and direction (e.g., {1.f, 0.f} moves right)
        float angularVelocity; // Rotation speed (degrees per second)

        MoveComponent() = default;

        MoveComponent(const sf::Vector2f& velocity, float angularVelocity)
            : velocity(velocity), angularVelocity(angularVelocity) {}
    };
}

#endif // MOVE_COMPONENT_HPP