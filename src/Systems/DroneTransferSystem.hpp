#ifndef DRONE_TRANSFER_SYSTEM_HPP
#define DRONE_TRANSFER_SYSTEM_HPP    

#include <execution>

#include "Game/GameEntityManager.hpp"

#include "Components/DroneTransferComponent.hpp"

namespace Systems {


    void DroneTransferSystem(Game::GameEntityManager& manager, float dt) {

        for(auto&& [id, transfer, faction, garisson] : manager.view<
            Components::DroneTransferComponent,
            Components::FactionComponent,
            Components::GarissonComponent>().each()) {
                
            if(faction.faction != transfer.faction){
                // if the factions changed, remove the order
                manager.removeComponent<Components::DroneTransferComponent>(id);
            }

            if(garisson.getDroneCount() > 0){
                manager.addOrReplaceComponent<Components::AttackOrderComponent>(transfer.source, transfer.source, transfer.target);
            }
        }
    }
}

#endif // DRONE_TRANSFER_SYSTEM_HPP