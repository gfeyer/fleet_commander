#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/TextComponent.hpp"

namespace Systems {

    void RenderSystem(std::unordered_map<int, Entity>& entities, sf::RenderWindow& window) {
        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();

            // Render SpriteComponent
            auto* sprite = entity.getComponent<Components::SpriteComponent>();
            if (sprite && transform) {
                sprite->sprite.setPosition(transform->getPosition());
                sprite->sprite.setRotation(transform->getRotation());
                sprite->sprite.setScale(transform->getScale());

                // Render the sprite
                window.draw(sprite->sprite);
            }

            // Render ShapeComponent
            auto* shape = entity.getComponent<Components::ShapeComponent>();
            if (shape && transform && shape->shape) {
                shape->shape->setPosition(transform->getPosition());
                shape->shape->setRotation(transform->getRotation());
                shape->shape->setScale(transform->getScale());
                window.draw(*shape->shape);
            }

            // Draw non-gui text
            auto* textComp = entity.getComponent<Components::TextComponent>();
            if (textComp) {
                window.draw(textComp->text);
            }
        }
    }
}

#endif // RENDER_SYSTEM_HPP