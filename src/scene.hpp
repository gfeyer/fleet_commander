#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>;
#include <memory>

class Entity;
class Scene{
private:
    std::vector<std::shared_ptr<Entity>> entities;
    sf::Sprite backgroundSprite;

public:
    Scene();
    ~Scene();   
    void update(float dt);
    void render(sf::RenderWindow& window);
    void handleInput(sf::Event& event);
};

#endif // SCENE_HPP