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

        DroneTransferComponent(EntityID source, EntityID target, Faction faction) : source(source), target(target), faction(faction) {}
    };
}

#endif // DRONE_TRANSFER_COMPONENT_HPP