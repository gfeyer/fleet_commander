#ifndef SHAPE_COMPONENT_HPP
#define SHAPE_COMPONENT_HPP

#include <sfml/Graphics.hpp>
#include <memory>

namespace Components {

    struct ShapeComponent {
        std::shared_ptr<sf::Shape> shape; // Polymorphic shared pointer to any sf::Shape

        // Default Constructor
        ShapeComponent() = default;

        // Constructor with shape
        ShapeComponent(std::shared_ptr<sf::Shape> shapePtr)
            : shape(shapePtr) {}

        // Utility to set fill color
        void setFillColor(const sf::Color& color) {
            if (shape) {
                shape->setFillColor(color);
            }
        }

        // Utility to set outline
        void setOutlineColor(const sf::Color& color) {
            if (shape) {
                shape->setOutlineColor(color);
            }
        }
    };
}

#endif // SHAPE_COMPONENT_HPP