#ifndef DRONE_TRANSFER_SYSTEM_HPP
#define DRONE_TRANSFER_SYSTEM_HPP    

#include "Game/GameEntityManager.hpp"

#include "Components/DroneTransferComponent.hpp"

namespace Systems {

    void DroneTransferSystem(Game::GameEntityManager& entityManager) {

        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {

            auto* droneTransferComp = entity.getComponent<Components::DroneTransferComponent>();

            if (droneTransferComp) {
                // Check if faction is the same
                auto* factionComp = entity.getComponent<Components::FactionComponent>();
                if(factionComp && factionComp->faction != droneTransferComp->faction){
                    entityManager.removeComponent<Components::DroneTransferComponent>(id);
                    continue;
                }

                // Check if there's any drones to transfer
                auto* garissonComp = entity.getComponent<Components::GarissonComponent>();
                if(garissonComp && garissonComp->getDroneCount() > 0){
                    auto source = droneTransferComp->source;
                    auto target = droneTransferComp->target;
                    entityManager.addComponent(source, Components::AttackOrderComponent{source, target});
                }
            }
        }
    }
}

#endif // DRONE_TRANSFER_SYSTEM_HPP