#ifndef ENTITY_OLD_HPP
#define ENTITY_OLD_HPP

#include <string>

#include <SFML/Graphics.hpp>

class EntityOld : public sf::Transformable{
// Base class for a game object
// Uses sf::Transformable to manage position, rotation and scale

protected:
 
    // Visual Representation
    sf::Sprite sprite;
    std::unique_ptr<sf::Shape> shape;

    // Bounding Box / Collision
    sf::FloatRect boundingBox;

    // Unique IDentifier
    std::string id;

public:
    EntityOld();
    virtual ~EntityOld();

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void handleInput(sf::Event& event) = 0;

    // Transform
    // void setPosition(sf::Vector2f pos);
    // void setPosition(float x, float y);
    // sf::Vector2f getPosition();

    // Collision Detection
    virtual bool checkCollision(const EntityOld& other) const;
    sf::FloatRect getBoundingBox() const;

    // Visual Representation
    void setSprite(sf::Sprite sprite);
    sf::Sprite getSprite() const;

    void setShape(std::unique_ptr<sf::Shape> shape);
    std::unique_ptr<sf::Shape> getShape() const;
};

#endif // ENTITY_OLD_HPP