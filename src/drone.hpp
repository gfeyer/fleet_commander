#ifndef DRONE_HPP
#define DRONE_HPP

#include "entity_old.hpp"
#include "gui.hpp"

class Drone : public EntityOld {
    private:
    sf::ConvexShape triangle;
    tgui::Label::Ptr label;
    void initialize();  

    public:
    Drone();
    Drone(sf::Vector2f pos, float rot, sf::Vector2f scale);
    ~Drone();

    void update(float dt) override;
    void handleInput(sf::Event& event) override;
    void render(sf::RenderWindow& window) override;  
};

#endif // DRONE_HPP