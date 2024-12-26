#ifndef ATTACK_ORDER_COMPONENT_HPP
#define ATTACK_ORDER_COMPONENT_HPP

#include "Core/Entity.hpp"
namespace Components {

    struct AttackOrderComponent {
        EntityID origin;
        EntityID target;
        bool isActivated = false;

        AttackOrderComponent(EntityID origin, EntityID target) : origin(origin), target(target), isActivated(false) {}
    };
}

#endif // ATTACK_ORDER_COMPONENT_HPP