#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <sfml/System.hpp>
#include <SFML/Graphics.hpp>

struct TransformComponent {
    sf::Vector2f position {0.f, 0.f}; // Default to origin (0,0)
    float rotation {0.f};             // Default to no rotation (0 degrees)
    sf::Vector2f scale {1.f, 1.f};    // Default to uniform scale (1,1)

    // Default Constructor
    TransformComponent() = default;

    // Parameterized Constructor
    TransformComponent(const sf::Vector2f& pos, float rot, const sf::Vector2f& scl)
        : position(pos), rotation(rot), scale(scl) {}
};

struct SpriteComponent {
    sf::Sprite sprite;

    SpriteComponent() = default;

    SpriteComponent(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    void setTexture(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }
};

#endif // COMPONENTS_HPP