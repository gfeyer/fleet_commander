#ifndef WINNING_CONDITIONS_SYSTEM_HPP
#define WINNING_CONDITIONS_SYSTEM_HPP

#include <unordered_map>
#include "Game/GameEntityManager.hpp"
#include "Components/FactionComponent.hpp"

namespace Systems {

    void GameStateSystem(Game::GameEntityManager& manager, float dt) {

        static float timer = 0.f;
        // Run this check every 5 seconds
        if(timer < 5.f){
            timer += dt;
            return;
        }
        timer = 0.f;

        std::unordered_map<Components::Faction, unsigned int> units;

        // check if both players have units on the map
        for(auto&& [id, faction] : manager.view<Components::FactionComponent>().each()) {
            units[faction.faction] += 1;
        }
            
        if(units[Components::Faction::PLAYER_1] == 0) {
            // Player1 has lost
            auto* gameState = manager.getGameStateComponent();
            gameState->winner = Components::Faction::PLAYER_2;
            gameState->isGameOver = true;
        }

        if (units[Components::Faction::PLAYER_2] == 0) {
            // Player2 has lost
            auto* gameState = manager.getGameStateComponent();
            gameState->winner = Components::Faction::PLAYER_1;
            gameState->isGameOver = true;
        }
    }
}

#endif // WINNING_CONDITIONS_SYSTEM_HPP