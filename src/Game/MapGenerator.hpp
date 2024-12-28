#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include <vector>
#include <cmath>
#include <random>
#include <SFML/System/Vector2.hpp> // Include sf::Vector2f

#include "Game/GameEntityManager.hpp"

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

    void GenerateRandomMap(Game::GameEntityManager& entityManager, float mapWidth, float mapHeight, unsigned int unitCount, float minDistance) {
        auto positionGenerator = Game::RandomPositionGenerator(mapWidth, mapHeight, minDistance);
        auto positions = positionGenerator.generateNonOverlappingPositions(unitCount);

        // player factory
        auto player1Faction = Components::Faction::PLAYER_1;
        float productionRate = 1.f;
        float shieldRegenRate = Utils::getRandomFloat(0.75f, 1.f);
        unsigned int capacity = Utils::getRandomFloat(8.f, 12.f);
        Game::createFactory(entityManager, "Factory #" + std::to_string(0), positions[0],player1Faction, productionRate, shieldRegenRate);
        Game::createPowerPlant(entityManager, "Power Plant #" + std::to_string(0), positions[1],player1Faction, shieldRegenRate, capacity);

        // Create Enemy Factories
        auto enemyFaction = Components::Faction::PLAYER_2;
        Game::createFactory(entityManager, "Factory #" + std::to_string(0), positions[2], enemyFaction, productionRate, shieldRegenRate);
        Game::createPowerPlant(entityManager, "Power Plant #" + std::to_string(0), positions[3], enemyFaction, shieldRegenRate, capacity);


        for(int i = 4; i < positions.size(); ++i){
        float coinFlip = Utils::getRandomFloat(0.f, 1.f);
        float shieldRegenRate = Utils::getRandomFloat(0.1f, 1.f);

            if(coinFlip < 0.5f){
                // Generate Factory
                auto productionRate = Utils::getRandomFloat(0.1f, 0.9f);
                Game::createFactory(entityManager, "Factory #" + std::to_string(i), positions[i], Components::Faction::NEUTRAL, productionRate, shieldRegenRate);
            } else{
                // Generate Power plant
                unsigned int capacity = Utils::getRandomFloat(5.f, 25.f);
                Game::createPowerPlant(entityManager, "Power Plant #" + std::to_string(i), positions[i], Components::Faction::NEUTRAL, shieldRegenRate, capacity);
            }
        }
    }

}

#endif // MAP_GENERATOR_HPP
