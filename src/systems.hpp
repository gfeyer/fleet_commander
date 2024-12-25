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
    }
}

#endif // SYSTEMS_HPP