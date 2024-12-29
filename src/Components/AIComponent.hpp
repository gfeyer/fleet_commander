#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include "Game/GameEntityManager.hpp"

namespace Components {
    struct AIComponent {
        float decisionTimer = 0.f;
        float decisionTimerMax = 1.f; // decide every second
        EntityID highlightedEntityID = 0;

        AIComponent(){}
    };
}

#endif // AI_COMPONENT_HPP