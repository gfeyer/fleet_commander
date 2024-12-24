#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include <SFML/Graphics.hpp>

class Entity{
// Entity is a base class for game objects such as sprites, positions, and basic behaviors.

protected:
    // Transform data
    sf::Vector2f position;
    float rotation;  
    sf::Vector2f scale;  

    // Visual Representation
    sf::Sprite sprite;
    std::unique_ptr<sf::Shape> shape;

    // Bounding Box / Collision
    sf::FloatRect boundingBox;

    // Unique IDentifier
    std::string id;

public:
    Entity(sf::Vector2f pos, float rot, sf::Vector2f scale);
    virtual ~Entity();

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void handleInput(sf::Event& event) = 0;

    // Transform
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();

    // Collision Detection
    virtual bool checkCollision(const Entity& other) const;
    sf::FloatRect getBoundingBox() const;

    // Visual Representation
    void setSprite(sf::Sprite sprite);
    sf::Sprite getSprite() const;

    void setShape(std::unique_ptr<sf::Shape> shape);
    std::unique_ptr<sf::Shape> getShape() const;
};

#endif // ENTITY_HPP