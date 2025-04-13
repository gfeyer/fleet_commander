#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components{
    struct SpriteComponent {
        sf::Sprite sprite;
        bool isVisible = true;
    };

}

#endif // SPRITE_COMPONENT_HPP