#ifndef GAME_STATE_COMPONENT_HPP
#define GAME_STATE_COMPONENT_HPP

#include <unordered_map>
#include "Components/FactionComponent.hpp"

namespace Components {
    struct GameStateComponent {
        std::unordered_map<Faction, int> playerDrones;
        std::unordered_map<Faction, int> playerEnergy;
        Faction winner = Faction::NEUTRAL;
        bool isGameOver = false;

        GameStateComponent(unsigned int playerCount) {
            if(playerCount == 1){
                playerDrones[Faction::PLAYER_1] = 0;
                playerEnergy[Faction::PLAYER_1] = 0;
            }
            else if(playerCount == 2){
                playerDrones[Faction::PLAYER_1] = 0;
                playerDrones[Faction::PLAYER_2] = 0;
                playerEnergy[Faction::PLAYER_1] = 0;
                playerEnergy[Faction::PLAYER_2] = 0;
            }
        }

        void ClearAllEnergy(){
            for(auto& [id, energy] : playerEnergy){
                energy = 0;
            }
        }
    };
}

#endif // GAME_STATE_COMPONENT_HPP