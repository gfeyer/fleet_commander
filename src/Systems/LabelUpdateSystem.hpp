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
    void LabelUpdateSystem(Game::GameEntityManager& manager, float dt) {
        auto entities = manager.getAllEntityIDs();
        for (auto id : entities) {
            auto* transform = manager.getComponent<Components::TransformComponent>(id);
            auto* labelComp = manager.getComponent<Components::LabelComponent>(id);

            if (labelComp && transform) {
                // Update the text position based on parent position + offset
                labelComp->text.setPosition(transform->getPosition() + labelComp->offset);
                labelComp->text2.setPosition(transform->getPosition());

                // Update the text on the label:
                auto* factory = manager.getComponent<Components::FactoryComponent>(id);
                auto* powerPlant = manager.getComponent<Components::PowerPlantComponent>(id);
                auto* drone = manager.getComponent<Components::DroneComponent>(id);
                auto* garisson = manager.getComponent<Components::GarissonComponent>(id);

                std::stringstream ss;
                if(factory){
                    char buffer[50];
                    // std::snprintf(buffer, sizeof(buffer), "Factory %d\n%.1f/s",id, factory->droneProductionRate);
                    std::snprintf(buffer, sizeof(buffer), "Factory\n%.1f/s",factory->droneProductionRate);
                    ss << buffer;
                }
                if(powerPlant){
                    char buffer[50];
                    // std::snprintf(buffer, sizeof(buffer), "FusionReactor %d\nCapacity: %d", id, powerPlant->capacity);
                    std::snprintf(buffer, sizeof(buffer), "FusionReactor\nCapacity: %d", powerPlant->capacity);
                    ss << buffer;
                }
                if(drone){
                    ss << drone->droneName;
                }
                if(garisson){
                    if (garisson->getDroneCount() > 0){
                        labelComp->text2.setString(std::to_string(garisson->getDroneCount()));
                        sf::FloatRect textBounds = labelComp->text2.getLocalBounds();
                        labelComp->text2.setOrigin(
                            textBounds.left + textBounds.width / 2.f, 
                            textBounds.top + textBounds.height / 2.f
                        );
                    }
                }

                // auto* shield = manager.getComponent<Components::ShieldComponent>();
                // if(shield){
                //     ss << "\nShield: " << shield->getShield() << "/" << shield->maxShield;
                // }
                labelComp->text.setString(ss.str());
            }
        }
    }
}

#endif // TEXT_UPDATE_SYSTEM_HPP