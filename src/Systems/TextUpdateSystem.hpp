#ifndef TEXT_UPDATE_SYSTEM_HPP
#define TEXT_UPDATE_SYSTEM_HPP

#include <unordered_map>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/TextComponent.hpp"

namespace Systems {
    void TextUpdateSystem(std::unordered_map<EntityID, Entity>& entities, float dt) {
        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* textComp = entity.getComponent<Components::TextComponent>();

            if (transform && textComp) {
                // Update the text position based on parent position + offset
                textComp->text.setPosition(transform->getPosition() + textComp->offset);
            }
        }
    }
}

#endif // TEXT_UPDATE_SYSTEM_HPP