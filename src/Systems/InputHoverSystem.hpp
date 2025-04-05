#ifndef INPUT_HOVER_SYSTEM_HPP
#define INPUT_HOVER_SYSTEM_HPP

#include <unordered_map>
#include <cassert>
#include <SFML/Graphics.hpp>


#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/HoverComponent.hpp"

#include "Utils/Logger.hpp"

#include "Game/GameEntityManager.hpp"

namespace Systems {
    void InputHoverSystem(Game::GameEntityManager& manager, const sf::RenderWindow& window) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        bool isHovered = false;
        sf::Vector2f hoverPosition;

        for (auto&& [id, transform, sprite, hover]: manager.view<Components::TransformComponent, Components::SpriteComponent, Components::HoverComponent>().each()) {
            // Check if mouse is within entity bounds
            if (sprite.sprite.getGlobalBounds().contains(worldPos)) {
                isHovered = true;
                hoverPosition = static_cast<sf::Vector2f>(mousePos);

                hover.isHovered = isHovered;
                hover.position = hoverPosition;
            } else {
                hover.isHovered = false;
            }
        }

        // Update cursor component
        for(auto&& [id, cursor, transform, sprite] : manager.view<Components::CursorComponent, Components::TransformComponent, Components::SpriteComponent>().each()) {
            if (isHovered) {

                sprite.sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_POINTER), true);
                sprite.sprite.setOrigin(sprite.sprite.getLocalBounds().width/2, sprite.sprite.getLocalBounds().height/2);
                transform.transform.setPosition(hoverPosition);
                transform.transform.setScale(0.15f, 0.15f);

                sprite.isVisible = true;
            }else{
                sprite.isVisible = false;
            }
        }
    }
}


#endif // INPUT_HOVER_SYSTEM_HPP