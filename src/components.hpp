#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <sfml/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

struct TagComponent {
    std::string tag;

    TagComponent(const std::string& tag) : tag(tag) {}
};

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

struct TextComponent {
    sf::Text text;
    sf::Vector2f offset; // Relative position to the parent

    TextComponent() = default;

    TextComponent(const std::string& label, const sf::Font& font, unsigned int fontSize, const sf::Color& color, sf::Vector2f offset = {0.f, 0.f}) {
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(fontSize);
        text.setFillColor(color);
        this->offset = offset;
    }

    void setText(const std::string& label) {
        text.setString(label);
    }
};

struct FactoryComponent {
    std::string factoryName;

    FactoryComponent(const std::string& factoryName) : factoryName(factoryName) {}
};

struct OutpostComponent {
    std::string outpostName;

    OutpostComponent(const std::string& outpostName) : outpostName(outpostName) {}
};


#endif // COMPONENTS_HPP