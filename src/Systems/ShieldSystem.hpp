#ifndef SHIELD_SYSTEM_HPP
#define SHIELD_SYSTEM_HPP

#include <unordered_map>
#include <cmath>

#include "Components/ShieldComponent.hpp"
#include "Core/Entity.hpp"
namespace Systems {
    void ShieldSystem(Game::GameEntityManager& entityManager, float dt) {

        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {
            auto* shield = entity.getComponent<Components::ShieldComponent>();
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