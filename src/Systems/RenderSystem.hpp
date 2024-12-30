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
        
        // 1. Draw selection, shield, sprite, shapes
        for(auto& [id, entity] : entities) {
            // Draw shapes/sprites/shields
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
                float radiusStep = 7.f;       // Space between concentric circles
                float thickness = 7.f;         // Circle thickness
                int pointCount = 50;           // Smoothness of the arc

                // Calculate full circles and remainder (using float logic for smooth rendering)
                float shieldValue = shield->currentShield;
                int fullCircles = static_cast<int>(shieldValue / 10.f); // Number of full circles
                float remainder = std::fmod(shieldValue, 10.f);         // Remaining fractional shield value

                // Draw Full Circles
                for (int i = 0; i < fullCircles; ++i) {
                    float currentRadius = baseRadius + (i * radiusStep);

                    sf::VertexArray arc = Utils::CreateArc(
                        center,
                        currentRadius,
                        thickness,
                        1.0f, // 100% full circle
                        pointCount,
                        sf::Color(0, 255, 255, 200)
                    );

                    window.draw(arc);
                }

                // Draw Partial Circle for Remainder
                if (remainder > 0.f) {
                    float currentRadius = baseRadius + (fullCircles * radiusStep);
                    float percentage = remainder / 10.0f; // Partial fill percentage (0.0 to 1.0)

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
        }

        // 2. Draw non gui text last
        for (auto& [id, entity] : entities) {

            // Draw non-gui text
            auto* textComp = entity.getComponent<Components::LabelComponent>();
            if (textComp) {
                window.draw(textComp->text);
            }
        }

        // 3. Draw Debug Symbols
        Entity& aiEntity = entityManager.getAIEntity();
        auto* aiComp = aiEntity.getComponent<Components::AIComponent>();
        if (aiComp && aiComp) {
            for (auto& target : aiComp->debug.pinkDebugTargets) {
                sf::CircleShape selectionShape(20.f);
                selectionShape.setOrigin(10.f, 10.f);
                selectionShape.setFillColor(sf::Color::Magenta);
                selectionShape.setPosition(target);
                window.draw(selectionShape);
            }

            for (auto& target : aiComp->debug.yellowDebugTargets) {
                sf::CircleShape selectionShape(20.f);
                selectionShape.setOrigin(10.f, 10.f);
                selectionShape.setFillColor(sf::Color::Yellow);
                selectionShape.setPosition(target);
                window.draw(selectionShape);
            }
        }
    }
}

#endif // RENDER_SYSTEM_HPP