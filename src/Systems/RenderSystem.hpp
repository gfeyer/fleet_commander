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
#include "Components/ShieldComponent.hpp"
#include "Components/GarissonComponent.hpp"

#include "Utils/Circle.hpp"

namespace Systems {

    void RenderSystem(Game::GameEntityManager& entityManager, sf::RenderWindow& window) {
        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {

            // Draw selectable component first (and draw sprite over it)
            auto* selectableComp = entity.getComponent<Components::SelectableComponent>();
            auto* transform = entity.getComponent<Components::TransformComponent>();
            if (selectableComp && selectableComp->isSelected && transform) {
                sf::CircleShape selectionShape(Config::FACTORY_SIZE);
                selectionShape.setOrigin(Config::FACTORY_SIZE, Config::FACTORY_SIZE);
                selectionShape.setFillColor(sf::Color(255,255,0,200));
                selectionShape.setPosition(transform->getPosition());
                window.draw(selectionShape);
            }

            // Draw Shield
            auto* shield = entity.getComponent<Components::ShieldComponent>();
            if (shield && transform) {
                sf::Vector2f center(transform->getPosition().x, transform->getPosition().y);
                float baseRadius = 50.f;       // Base radius for the first circle
                float radiusStep = 5.f;        // Space between concentric circles
                float thickness = 5.f;         // Circle thickness
                int pointCount = 50;           // Smoothness of the arc

                int fullCircles = shield->currentShield / 5; // Number of full circles
                int remainder = shield->currentShield % 5;   // Remaining units for a partial circle

                // Draw Full Circles
                for (int i = 0; i < fullCircles; ++i) {
                    float currentRadius = baseRadius + (i * radiusStep);

                    sf::VertexArray arc = Utils::CreateArc(
                        center,
                        currentRadius,
                        thickness,
                        1.0f, // 100% circle
                        pointCount,
                        sf::Color(0, 255, 255, 200)
                    );

                    window.draw(arc);
                }

                // Draw Partial Circle for Remainder
                if (remainder > 0) {
                    float currentRadius = baseRadius + (fullCircles * radiusStep);
                    float percentage = float(remainder) / 5.0f; // Remainder as percentage of a full circle

                    sf::VertexArray arc = Utils::CreateArc(
                        center,
                        currentRadius,
                        thickness,
                        percentage,
                        pointCount,
                        sf::Color(0, 255, 255, 200) // Yellow for the partial arc
                    );

                    window.draw(arc);
                }
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

                auto* faction = entity.getComponent<Components::FactionComponent>();
                if (faction) {
                    if (faction->faction == Components::Faction::PLAYER_1) {
                        shape->shape->setFillColor(sf::Color::Red);
                    }else if(faction->faction == Components::Faction::PLAYER_2) {
                        shape->shape->setFillColor(sf::Color::Blue);
                    }else{
                        // shape->shape->setFillColor(sf::Color::White);
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