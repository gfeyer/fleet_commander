#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"
#include "Game/GameEntityManager.hpp"

class Scene{
private:
    Game::GameEntityManager entityManager;
    std::unique_ptr<tgui::Gui> gui;
    sf::RenderWindow& windowRef;
    
    // Camera
    sf::View camera;
    sf::Vector2f cameraPosition;
    float cameraSpeed = 200.f;

public:
    Scene(sf::RenderWindow& window);
    ~Scene();   
    void update(float dt);
    void render();
    void handleInput(sf::Event& event);
};

#endif // SCENE_HPP