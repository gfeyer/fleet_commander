#ifndef INPUT_HOVER_SYSTEM_HPP
#define INPUT_HOVER_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/HoverComponent.hpp"

#include "Utils/Logger.hpp"

namespace Systems {
    void InputHoverSystem(std::unordered_map<int, Entity>& entities, const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* shapeComp = entity.getComponent<Components::ShapeComponent>();
            auto* hoverComp = entity.getComponent<Components::HoverComponent>();

            if (transform && shapeComp && hoverComp) {
                // Check if mouse is within entity bounds
                if (shapeComp->shape->getGlobalBounds().contains(worldPos)) {
                    hoverComp->isHovered = true;
                    hoverComp->position = worldPos;
                } else {
                    hoverComp->isHovered = false;
                }
            }
        }
    }
}


#endif // INPUT_HOVER_SYSTEM_HPP