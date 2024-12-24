#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "entity.hpp"

class Factory : public Entity {
    public:
        Factory(sf::Vector2f pos, float rot, sf::Vector2f scale);
        ~Factory();
        void update(float dt) override;
        void handleInput(sf::Event& event) override;
};

#endif // FACTORY_HPP