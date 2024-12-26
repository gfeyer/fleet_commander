#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Core/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/FactionComponent.hpp"

namespace Systems {

    void RenderSystem(std::unordered_map<EntityID, Entity>& entities, sf::RenderWindow& window) {
        for (auto& [id, entity] : entities) {
            auto* transform = entity.getComponent<Components::TransformComponent>();
            auto* faction = entity.getComponent<Components::FactionComponent>();

            // Draw selectable component first (and draw sprite over it)
            auto* selectableComp = entity.getComponent<Components::SelectableComponent>();
            if (selectableComp && selectableComp->isSelected && transform) {
                sf::CircleShape selectionShape(Config::FACTORY_SIZE);
                selectionShape.setOrigin(Config::FACTORY_SIZE/2, Config::FACTORY_SIZE/2);
                selectionShape.setFillColor(sf::Color::Yellow);
                selectionShape.setPosition(transform->getPosition());
                window.draw(selectionShape);
            }

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

                if (faction) {
                    if (faction->factionID == 1) {
                        shape->shape->setFillColor(sf::Color::Red);
                    }
                }

                window.draw(*shape->shape);
            }

            // Draw non-gui text
            auto* textComp = entity.getComponent<Components::LabelComponent>();
            if (textComp) {
                window.draw(textComp->text);
            }
        }
    }
}

#endif // RENDER_SYSTEM_HPP