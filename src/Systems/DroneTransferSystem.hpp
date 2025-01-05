#ifndef DRONE_TRANSFER_SYSTEM_HPP
#define DRONE_TRANSFER_SYSTEM_HPP    

#include "Game/GameEntityManager.hpp"

#include "Components/DroneTransferComponent.hpp"

namespace Systems {

    void DroneTransferSystem(Game::GameEntityManager& manager, float dt) {

        auto entities = manager.getAllEntityIDs();
        for (auto id : entities) {

            auto* droneTransferComp = manager.getComponent<Components::DroneTransferComponent>(id);

            if (droneTransferComp) {
                // Check if faction is the same
                auto* factionComp = manager.getComponent<Components::FactionComponent>(id);
                if(factionComp && factionComp->faction != droneTransferComp->faction){
                    manager.removeComponent<Components::DroneTransferComponent>(id);
                    continue;
                }

                // Check if there's any drones to transfer
                auto* garissonComp = manager.getComponent<Components::GarissonComponent>(id);
                if(garissonComp && garissonComp->getDroneCount() > 0){
                    auto source = droneTransferComp->source;
                    auto target = droneTransferComp->target;
                    manager.addOrReplaceComponent<Components::AttackOrderComponent>(source, source, target);
                }
            }
        }
    }
}

#endif // DRONE_TRANSFER_SYSTEM_HPP