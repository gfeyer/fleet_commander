#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"
#include "Core/Entity.hpp"

class Scene{
private:
    std::unordered_map<int, Entity> entities;
    std::unique_ptr<tgui::Gui> gui;
    sf::RenderWindow& windowRef;

public:
    Scene(sf::RenderWindow& window);
    ~Scene();   
    void update(float dt);
    void render();
    void handleInput(sf::Event& event);
};

#endif // SCENE_HPP