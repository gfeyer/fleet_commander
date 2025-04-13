#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components{
    struct SpriteComponent {
        sf::Sprite sprite;
        bool isVisible = true;
        int layer = 0;
    };

}

#endif // SPRITE_COMPONENT_HPP