#ifndef TEXT_UPDATE_SYSTEM_HPP
#define TEXT_UPDATE_SYSTEM_HPP

#include <unordered_map>
#include <sstream>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/LabelComponent.hpp"

namespace Systems {
    void LabelUpdateSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {
        for (auto& [id, entity] : entities) {
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

                labelComp->text.setString(ss.str());

            }
        }
    }
}

#endif // TEXT_UPDATE_SYSTEM_HPP