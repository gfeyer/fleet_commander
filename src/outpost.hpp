#ifndef OUTPOST_HPP
#define OUTPOST_HPP

#include "gui.hpp"
#include "entity.hpp"

class Outpost : public Entity
{
    private:
        sf::CircleShape circleShape;
        tgui::Label::Ptr label;

        void initialize();

    public:
        Outpost();
        Outpost(sf::Vector2f pos, float rot, sf::Vector2f scale);
        ~Outpost();

        void update(float dt) override;
        void handleInput(sf::Event& event) override;
        void render(sf::RenderWindow& window) override;

};


#endif // OUTPOST_HPP