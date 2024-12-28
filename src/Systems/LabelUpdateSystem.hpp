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
        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* labelComp = entity.getComponent<Components::LabelComponent>();

            if (labelComp && transform) {
                // Update the text position based on parent position + offset
                labelComp->text.setPosition(transform->getPosition() + labelComp->offset);

                // Update the text on the label:
                auto* factory = entity.getComponent<Components::FactoryComponent>();
                auto* powerPlant = entity.getComponent<Components::PowerPlantComponent>();
                auto* drone = entity.getComponent<Components::DroneComponent>();
                auto* garisson = entity.getComponent<Components::GarissonComponent>();

                std::stringstream ss;
                if(factory){
                    ss << factory->factoryName;
                }
                if(powerPlant){
                    // ss << powerPlant->powerPlantName;
                    ss << "FusionReactor\nCapacity: " << powerPlant->capacity;
                }
                if(drone){
                    ss << drone->droneName;
                }
                if(garisson){
                    if (garisson->getDroneCount() > 0){
                        ss << "\nDrones: " << garisson->getDroneCount();
                    }
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