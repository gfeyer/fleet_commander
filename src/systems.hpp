#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "entity.hpp"
#include "components.hpp"
#include "util/logger.hpp"

void RenderSystem(std::unordered_map<int, Entity>& entities, sf::RenderWindow& window) {
    for (auto& [id, entity] : entities) {
        auto* sprite = entity.getComponent<SpriteComponent>();
        auto* transform = entity.getComponent<TransformComponent>();

        // Check if both SpriteComponent and TransformComponent exist
        if (sprite && transform) {
            // Apply transform properties
            // log_info << "Rendering entity " << id << " with position (" << transform->position.x << ", " << transform->position.y << "), rotation " << transform->rotation << ", and scale (" << transform->scale.x << ", " << transform->scale.y << ")";
            sprite->sprite.setPosition(transform->position);
            sprite->sprite.setRotation(transform->rotation);
            sprite->sprite.setScale(transform->scale);

            // Render the sprite
            window.draw(sprite->sprite);
        }
    }
}

#endif // SYSTEMS_HPP