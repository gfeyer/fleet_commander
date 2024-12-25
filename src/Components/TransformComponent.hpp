#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <sfml/System.hpp>
#include <SFML/Graphics.hpp>

namespace Components {
    
    struct TransformComponent {
        sf::Transformable transform;

        TransformComponent() = default;

        TransformComponent(const sf::Vector2f& pos, float rot, const sf::Vector2f& scl) {
            transform.setPosition(pos);
            transform.setRotation(rot);
            transform.setScale(scl);
        }

        sf::Vector2f getPosition() const { return transform.getPosition(); }
        float getRotation() const { return transform.getRotation(); }
        sf::Vector2f getScale() const { return transform.getScale(); }
    };

}

#endif // TRANSFORM_COMPONENT_HPP