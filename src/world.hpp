#include <SFML/Graphics.hpp>
#include <iostream>;

class World{
    public:
        World();
        ~World();

        void update(float dt);
        void render(sf::RenderWindow& window);
};