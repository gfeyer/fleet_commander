#include "entity_old.hpp"

#include "util/logger.hpp"

EntityOld::EntityOld() : sf::Transformable()
{
}

EntityOld::~EntityOld()
{
}

void EntityOld::render(sf::RenderWindow &window)
{
    if(sprite.getTexture() != nullptr){
        window.draw(sprite);
    }else if(shape != nullptr){
        window.draw(*shape);
    }
}

bool EntityOld::checkCollision(const EntityOld &other) const
{
    return sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds());
}

void EntityOld::setShape(std::unique_ptr<sf::Shape> shape)
{
    this->shape = std::move(shape);
}
