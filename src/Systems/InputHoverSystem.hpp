#ifndef INPUT_HOVER_SYSTEM_HPP
#define INPUT_HOVER_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>


#include "Components/TransformComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/HoverComponent.hpp"

#include "Utils/Logger.hpp"

#include "Game/GameEntityManager.hpp"

namespace Systems {
    void InputHoverSystem(Game::GameEntityManager& manager, const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        for (auto&& [id, transform, shape, hover]: manager.view<Components::TransformComponent, Components::ShapeComponent, Components::HoverComponent>().each()) {
            // Check if mouse is within entity bounds
            if (shape.shape->getGlobalBounds().contains(worldPos)) {
                hover.isHovered = true;
                // hoverComp->position = worldPos;
                hover.position = static_cast<sf::Vector2f>(mousePos);

            } else {
                hover.isHovered = false;
            }
        }
    }
}


#endif // INPUT_HOVER_SYSTEM_HPP