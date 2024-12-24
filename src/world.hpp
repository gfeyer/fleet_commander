#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>;
#include <memory>

class Entity;
class World{
private:
    std::vector<std::shared_ptr<Entity>> entities;

public:
    World();
    ~World();   
    void update(float dt);
    void render(sf::RenderWindow& window);
    void handleInput(sf::Event& event);
};

#endif // WORLD_HPP