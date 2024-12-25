#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "entity.hpp"
#include "components.hpp"
#include "util/logger.hpp"

void RenderSystem(std::unordered_map<int, Entity>& entities, sf::RenderWindow& window) {
    for (auto& [id, entity] : entities) {
        auto* transform = entity.getComponent<TransformComponent>();

        // Render SpriteComponent
        auto* sprite = entity.getComponent<SpriteComponent>();
        if (sprite && transform) {
            sprite->sprite.setPosition(transform->getPosition());
            sprite->sprite.setRotation(transform->getRotation());
            sprite->sprite.setScale(transform->getScale());

            // Render the sprite
            window.draw(sprite->sprite);
        }

        // Render ShapeComponent
        auto* shape = entity.getComponent<ShapeComponent>();
        if (shape && transform && shape->shape) {
            shape->shape->setPosition(transform->getPosition());
            shape->shape->setRotation(transform->getRotation());
            shape->shape->setScale(transform->getScale());
            window.draw(*shape->shape);
        }

        // Draw non-gui text
        auto* textComp = entity.getComponent<TextComponent>();
        if (textComp) {
            window.draw(textComp->text);
        }
    }
}

void MovementSystem(std::unordered_map<int, Entity>& entities, float dt) {
    for (auto& [id, entity] : entities) {
        auto* transform = entity.getComponent<TransformComponent>();
        auto* move = entity.getComponent<MoveComponent>();

        if (transform && move) {
            // Update position based on velocity
            sf::Vector2f newPosition = transform->getPosition() + move->velocity * dt;
            transform->transform.setPosition(newPosition);

            if (move->velocity.x != 0.f || move->velocity.y != 0.f) {
                float angle = std::atan2(move->velocity.y, move->velocity.x) * Config::RAD_TO_DEG;
                transform->transform.setRotation(angle + 90.f); // +90 to align triangle tip upwards
            }

            // Update rotation based on angular velocity
            float newRotation = transform->getRotation() + move->angularVelocity * dt;
            transform->transform.setRotation(newRotation);
        }
    }
}

void TextUpdateSystem(std::unordered_map<int, Entity>& entities, float dt) {
    for (auto& [id, entity] : entities) {
        auto* transform = entity.getComponent<TransformComponent>();
        auto* textComp = entity.getComponent<TextComponent>();

        if (transform && textComp) {
            // Update the text position based on parent position + offset
            textComp->text.setPosition(transform->getPosition() + textComp->offset);
        }
    }
}


#endif // SYSTEMS_HPP