#ifndef DRONE_TRANSFER_COMPONENT_HPP
#define DRONE_TRANSFER_COMPONENT_HPP

#include <utility>
#include <set>

#include "Game/GameEntityManager.hpp"

namespace Components {

    struct DroneTransferComponent {
        EntityID source;
        EntityID target;
        Faction faction;    // Faction that placed the original order

        // Line animation
        // float currentDistance = 0.f; // Animation state per transfer line
        // float speed = 1500.f;         // Pixels per second
        // sf::Vector2f dotPosition;    // Calculated position of the animated dot

        DroneTransferComponent(EntityID source, EntityID target, Faction faction) : source(source), target(target), faction(faction) {}
    };
}

#endif // DRONE_TRANSFER_COMPONENT_HPP