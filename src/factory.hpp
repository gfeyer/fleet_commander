#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "entity.hpp"
#include "gui.hpp"

class Factory : public Entity {
    private:
        sf::RectangleShape rectangleShape;
        tgui::Label::Ptr label;

    void initialize();

    public:
        Factory();
        Factory(sf::Vector2f pos, float rot, sf::Vector2f scale);
        ~Factory();
        void update(float dt) override;
        void handleInput(sf::Event& event) override;
        void render(sf::RenderWindow& window) override;

};

#endif // FACTORY_HPP