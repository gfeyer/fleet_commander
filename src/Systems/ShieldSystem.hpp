#ifndef SHIELD_SYSTEM_HPP
#define SHIELD_SYSTEM_HPP

#include <unordered_map>
#include <cmath>

#include "Game/GameEntityManager.hpp"
#include "Components/ShieldComponent.hpp"

namespace Systems {
    void ShieldSystem(Game::GameEntityManager& manager, float dt) {

        auto entities = manager.getAllEntityIDs();
        for (auto id : entities) {
            auto* shield = manager.getComponent<Components::ShieldComponent>(id);
            if (shield) {
                // Skip if shield is already full
                if(shield->maxShield == shield->currentShield){
                    continue;
                }

                // Regenerate shield smoothly based on regenRate and delta time (dt)
                shield->currentShield += shield->regenRate * dt;

                // Clamp shield to maxShield to avoid overshooting
                if (shield->currentShield > shield->maxShield) {
                    shield->currentShield = shield->maxShield;
                }
            }
        }
    }
}


#endif // SHIELD_SYSTEM_HPP