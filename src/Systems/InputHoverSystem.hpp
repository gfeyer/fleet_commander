#ifndef INPUT_HOVER_SYSTEM_HPP
#define INPUT_HOVER_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/HoverComponent.hpp"

#include "Utils/Logger.hpp"

#include "Game/GameEntityManager.hpp"

namespace Systems {
    void InputHoverSystem(Game::GameEntityManager& manager, const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        auto& entities = manager.getAllEntityIDs();
        for (auto id: entities) {

            auto* transform = manager.getComponent<Components::TransformComponent>(id);
            auto* shapeComp = manager.getComponent<Components::ShapeComponent>(id);
            auto* hoverComp = manager.getComponent<Components::HoverComponent>(id);

            if (transform && shapeComp && hoverComp) {
                // Check if mouse is within entity bounds
                if (shapeComp->shape->getGlobalBounds().contains(worldPos)) {
                    hoverComp->isHovered = true;
                    // hoverComp->position = worldPos;
                    hoverComp->position = static_cast<sf::Vector2f>(mousePos);

                } else {
                    hoverComp->isHovered = false;
                }
            }
        }
    }
}


#endif // INPUT_HOVER_SYSTEM_HPP