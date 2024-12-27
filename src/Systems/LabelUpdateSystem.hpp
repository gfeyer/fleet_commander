#ifndef TEXT_UPDATE_SYSTEM_HPP
#define TEXT_UPDATE_SYSTEM_HPP

#include <unordered_map>
#include <sstream>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/ShieldComponent.hpp"
#include "Components/GarissonComponent.hpp"

#include "Game/GameEntityManager.hpp"

namespace Systems {
    void LabelUpdateSystem(Game::GameEntityManager& entityManager, float dt) {
        // Get all entities by IDs
        const auto& entityIDs = entityManager.getAllEntityIDs();

        for (EntityID id : entityIDs) {
            Entity& entity = entityManager.getEntity(id); // Access entity by ID
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* labelComp = entity.getComponent<Components::LabelComponent>();

            if (labelComp && transform) {
                // Update the text position based on parent position + offset
                labelComp->text.setPosition(transform->getPosition() + labelComp->offset);

                // Update the text on the label:
                auto* factory = entity.getComponent<Components::FactoryComponent>();
                auto* outpost = entity.getComponent<Components::OutpostComponent>();
                auto* drone = entity.getComponent<Components::DroneComponent>();
                auto* garisson = entity.getComponent<Components::GarissonComponent>();

                std::stringstream ss;
                if(factory){
                    ss << factory->factoryName;
                }
                if(outpost){
                    ss << outpost->outpostName;
                }
                if(drone){
                    ss << drone->droneName;
                }
                if(garisson){
                    ss << "\nDrones: " << garisson->getDroneCount();
                }

                // auto* shield = entity.getComponent<Components::ShieldComponent>();
                // if(shield){
                //     ss << "\nShield: " << shield->getShield() << "/" << shield->maxShield;
                // }
                labelComp->text.setString(ss.str());
            }
        }
    }
}

#endif // TEXT_UPDATE_SYSTEM_HPP