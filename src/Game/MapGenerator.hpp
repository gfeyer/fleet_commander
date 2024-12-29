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

    float calculateDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void GenerateRandomMap(Game::GameEntityManager& entityManager, float mapWidth, float mapHeight, int unitCount, float minDistance) {
        float minPlayerDistance = 300.0f; // Minimum distance between players

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(0.0f, mapWidth);
        std::uniform_real_distribution<float> distY(0.0f, mapHeight);

        // Generate starting positions for Player 1 and Player 2
        sf::Vector2f player1Start, player2Start;
        bool validPlacement = false;

        while (!validPlacement) {
            player1Start = {distX(gen), distY(gen)};
            player2Start = {distX(gen), distY(gen)};

            // Ensure players are sufficiently far apart
            if (calculateDistance(player1Start, player2Start) >= minPlayerDistance) {
                validPlacement = true;
            }
        }

        // Place Player 1 Structures (Factory + Power Plant)
        sf::Vector2f player1FactoryPos = player1Start;
        sf::Vector2f player1PowerPlantPos = {player1Start.x + Utils::getRandomFloat(50.f, 150.f), player1Start.y + Utils::getRandomFloat(50.f, 150.f)};

        auto player1Faction = Components::Faction::PLAYER_1;
        float productionRate = 1.f;
        float shieldRegenRate = Utils::getRandomFloat(0.75f, 1.f);
        unsigned int capacity = Utils::getRandomFloat(13.f, 20.f);

        Game::createFactory(entityManager, "Factory #0", player1FactoryPos, player1Faction, productionRate, shieldRegenRate);
        Game::createPowerPlant(entityManager, "Power Plant #0", player1PowerPlantPos, player1Faction, shieldRegenRate, capacity);

        // Place Player 2 Structures (Factory + Power Plant)
        sf::Vector2f player2FactoryPos = player2Start;
        sf::Vector2f player2PowerPlantPos = {player2Start.x + Utils::getRandomFloat(50.f, 150.f), player2Start.y + Utils::getRandomFloat(50.f, 150.f)};

        auto player2Faction = Components::Faction::PLAYER_2;

        Game::createFactory(entityManager, "Factory #0", player2FactoryPos, player2Faction, productionRate, shieldRegenRate);
        Game::createPowerPlant(entityManager, "Power Plant #0", player2PowerPlantPos, player2Faction, shieldRegenRate, capacity);

        // Generate Remaining Units Randomly
        Game::RandomPositionGenerator generator(mapWidth, mapHeight, minDistance);
        auto positions = generator.generateNonOverlappingPositions(unitCount); // Adjust count as needed

        for (size_t i = 0; i < positions.size(); ++i) {
            float coinFlip = Utils::getRandomFloat(0.f, 1.f);
            float shieldRegenRate = Utils::getRandomFloat(0.1f, 1.f);

            if (coinFlip > 0.5f) {
                // Generate Factory
                auto productionRate = Utils::getRandomFloat(0.1f, 0.9f);
                Game::createFactory(entityManager, "Factory #" + std::to_string(i), positions[i], Components::Faction::NEUTRAL, productionRate, shieldRegenRate);
            } else {
                // Generate Power plant
                unsigned int capacity = Utils::getRandomFloat(5.f, 25.f);
                Game::createPowerPlant(entityManager, "Power Plant #" + std::to_string(i), positions[i], Components::Faction::NEUTRAL, shieldRegenRate, capacity);
            }
        }
    }

}

#endif // MAP_GENERATOR_HPP

