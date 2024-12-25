#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <sfml/System.hpp>

struct TransformComponent {
    sf::Vector2f position;
    float rotation;
    sf::Vector2f scale;
};

#endif // COMPONENTS_HPP