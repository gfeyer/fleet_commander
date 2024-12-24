#include "entity.hpp"

#include "util/logger.hpp"

Entity::Entity() : sf::Transformable()
{
}

Entity::~Entity()
{
}

void Entity::render(sf::RenderWindow &window)
{
    if(sprite.getTexture() != nullptr){
        window.draw(sprite);
    }else if(shape != nullptr){
        window.draw(*shape);
    }
}

bool Entity::checkCollision(const Entity &other) const
{
    return sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds());
}

void Entity::setShape(std::unique_ptr<sf::Shape> shape)
{
    this->shape = std::move(shape);
}
