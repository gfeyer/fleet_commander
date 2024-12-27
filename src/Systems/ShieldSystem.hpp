#ifndef SHIELD_SYSTEM_HPP
#define SHIELD_SYSTEM_HPP

#include <unordered_map>
#include <cmath>

#include "Components/ShieldComponent.hpp"
#include "Core/Entity.hpp"
namespace Systems {
    void ShieldSystem(Game::GameEntityManager& entityManager, float dt) {

        // Get all entities by IDs
        const auto& entityIDs = entityManager.getAllEntityIDs();

        for (EntityID id : entityIDs) {
            Entity& entity = entityManager.getEntity(id); // Access entity by ID
            auto* shield = entity.getComponent<Components::ShieldComponent>();
            if (shield) {
                if(shield->maxShield == shield->currentShield){
                    continue;
                }

                shield->regenTimer += dt;
                if (shield->regenTimer >= shield->regenRate) {
                    shield->regenTimer = 0.f;
                    shield->incrementShield();
                }
            }
        }
    }
}


#endif // SHIELD_SYSTEM_HPP