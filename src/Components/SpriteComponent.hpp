#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components{
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
}

#endif // SPRITE_COMPONENT_HPP