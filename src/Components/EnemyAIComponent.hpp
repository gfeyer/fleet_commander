#ifndef ENEMY_AI_COMPONENT_HPP
#define ENEMY_AI_COMPONENT_HPP

namespace Components {
    struct EnemyAIComponent {
        float decisionTimer = 0.f;
        float decisionTimerMax = 3.f; // decide every second
    };
}

#endif // ENEMY_AI_COMPONENT_HPP