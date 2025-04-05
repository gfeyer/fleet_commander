#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/FactionComponent.hpp"
#include "Components/ShieldComponent.hpp"
#include "Components/GarissonComponent.hpp"
#include "Components/DroneTransferComponent.hpp"

#include "Utils/Graphics.hpp"
#include "Config.hpp"

namespace Systems {

    void RenderSystem(Game::GameEntityManager& manager, sf::RenderWindow& window) {
        auto entities = manager.getAllEntityIDs();
        

        // Layer 0
        // Background
        // Save current view
        sf::View originalView = window.getView();
        // Set to default view (fixed background)
        window.setView(window.getDefaultView());
        // Draw background (won't move with game camera)
        const auto& backgroundTexture = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::BACKGROUND);
        sf::Sprite background(backgroundTexture);
        background.setScale(2.f, 2.f);
        window.draw(background);

        // Restore game view
        window.setView(originalView);

        // Layer 1

        // Draw transfer lines
        for(auto&& [entityID, transform, transfer] : 
                    manager.view<
                        Components::TransformComponent, 
                        Components::DroneTransferComponent
                    >().each()) {
            
            auto* targetTransform = manager.getComponent<Components::TransformComponent>(transfer.target);
            if(targetTransform){
                sf::Color transparentWhite(255, 255, 255, 128); // 50% Transparent White 
                Utils::drawGradientDottedLine(window, transform.getPosition(), targetTransform->getPosition(), 10.f);
            }
        }

        // Draw Selection
        for(auto&& [id, transform, selectable] : manager.view<
                    Components::TransformComponent,
                    Components::SelectableComponent>().each()) {
                        
            if(selectable.isSelected){
                sf::CircleShape selectionShape(Config::FACTORY_SIZE);
                selectionShape.setOrigin(Config::FACTORY_SIZE, Config::FACTORY_SIZE);
                selectionShape.setFillColor(sf::Color(255,255,0,200));
                selectionShape.setPosition(transform.getPosition());
                window.draw(selectionShape);

                // sf::Sprite sprite;
                // const auto& texture = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_SHIELD);
                // sprite.setTexture(texture, true);
                // sprite.setScale(Config::SCALE_FACTOR*1.5, Config::SCALE_FACTOR*1.5);
                // sprite.setPosition(transform.getPosition());
                // sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
                // window.draw(sprite);
            }
        }

        // Draw Sprites
        for(auto&& [id, transform, sprite] : manager.view<
                    Components::TransformComponent, 
                    Components::SpriteComponent
                >().each()) {
            
            if(sprite.isVisible == false) continue;
            
            sprite.sprite.setPosition(transform.getPosition());
            sprite.sprite.setRotation(transform.getRotation());
            sprite.sprite.setScale(transform.getScale());
            window.draw(sprite.sprite);
        }

        // Draw Shields
        for(auto&& [id, transform, shield] : manager.view<
                    Components::TransformComponent, 
                    Components::ShieldComponent
                >().each()) {
            
            float multiplier = 0.5f + shield.currentShield/7.f;
            sf::Sprite sprite;
            const auto& texture = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_SHIELD);
            sprite.setTexture(texture, true);
            sprite.setScale(Config::SCALE_FACTOR*multiplier, Config::SCALE_FACTOR*multiplier);
            sprite.setPosition(transform.getPosition());
            sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
            window.draw(sprite);
            
            // sf::Vector2f center(transform.getPosition().x, transform.getPosition().y);
            // float baseRadius = 128.f;       // Base radius for the first circle
            // float radiusStep = 15.f;       // Space between concentric circles
            // float thickness = 5.f;         // Circle thickness
            // int pointCount = 50;           // Smoothness of the arc

            // // Calculate full circles and remainder (using float logic for smooth rendering)
            // float shieldValue = shield.currentShield;
            // int fullCircles = static_cast<int>(shieldValue / 10.f); // Number of full circles
            // float remainder = std::fmod(shieldValue, 10.f);         // Remaining fractional shield value

            // // Draw Full Circles
            // for (int i = 0; i < fullCircles; ++i) {
            //     float currentRadius = baseRadius + (i * radiusStep);

            //     sf::VertexArray arc = Utils::CreateArc(
            //         center,
            //         currentRadius,
            //         thickness,
            //         1.0f, // 100% full circle
            //         pointCount,
            //         sf::Color(0, 255, 255, 200)
            //     );

            //     window.draw(arc);
            // }

            // // Draw Partial Circle for Remainder
            // if (remainder > 0.f) {
            //     float currentRadius = baseRadius + (fullCircles * radiusStep);
            //     float percentage = remainder / 10.0f; // Partial fill percentage (0.0 to 1.0)

            //     sf::VertexArray arc = Utils::CreateArc(
            //         center,
            //         currentRadius,
            //         thickness,
            //         percentage,
            //         pointCount,
            //         sf::Color(0, 255, 255, 200) // Yellow for the partial arc
            //     );
            //     window.draw(arc);
            // }
        }

        // Draw Shapes
        for(auto&& [id, transform, shape] : manager.view<
                    Components::TransformComponent, 
                    Components::ShapeComponent
                >().each()) {
            
            shape.shape->setPosition(transform.getPosition());
            shape.shape->setRotation(transform.getRotation());
            shape.shape->setScale(transform.getScale());

            auto* faction = manager.getComponent<Components::FactionComponent>(id);
            if (faction) {
                if (faction->faction == Components::Faction::PLAYER_1) {
                    shape.shape->setFillColor(sf::Color::Red);
                }else if(faction->faction == Components::Faction::PLAYER_2) {
                    shape.shape->setFillColor(sf::Color::Blue);
                }else{
                    // shape->shape->setFillColor(sf::Color::White);
                }
            }
            window.draw(*shape.shape);
        }

        // Draw labels (non-gui)
        for (auto&& [id, label] : manager.view<Components::LabelComponent>().each()) {
            window.draw(label.text);
            window.draw(label.text2);
        }

        // Draw Debug Symbols
        auto* aiComp = manager.getAIComponent();
        if (aiComp && Config::ENABLE_DEBUG_SYMBOLS) { 
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