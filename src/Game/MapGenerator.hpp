#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include <vector>
#include <cmath>
#include <random>
#include <SFML/System/Vector2.hpp> // Include sf::Vector2f

namespace Game {

    class RandomPositionGenerator {
    public:
        RandomPositionGenerator(float mapWidth, float mapHeight, float minDistance)
            : mapWidth(mapWidth), mapHeight(mapHeight), minDistance(minDistance),
              gen(rd()), distX(0.0f, mapWidth), distY(0.0f, mapHeight) {}

        std::vector<sf::Vector2f> generateNonOverlappingPositions(int unitCount) {
            std::vector<sf::Vector2f> positions;
            int maxAttempts = 10000;
            int attempts = 0;

            while (positions.size() < unitCount && attempts < maxAttempts) {
                sf::Vector2f newPos = {distX(gen), distY(gen)};
                if (!isOverlapping(newPos, positions)) {
                    positions.push_back(newPos);
                }
                attempts++;
            }

            return positions;
        }

    private:
        float mapWidth, mapHeight, minDistance;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<float> distX;
        std::uniform_real_distribution<float> distY;

        bool isOverlapping(const sf::Vector2f& pos, const std::vector<sf::Vector2f>& positions) {
            for (const auto& other : positions) {
                float dx = pos.x - other.x;
                float dy = pos.y - other.y;
                float distance = std::sqrt(dx * dx + dy * dy);
                if (distance < minDistance) {
                    return true;
                }
            }
            return false;
        }
    };

    void GenerateRandomMap(float mapWidth, float mapHeight, unsigned int unitCount) {
    }

}

#endif // MAP_GENERATOR_HPP
