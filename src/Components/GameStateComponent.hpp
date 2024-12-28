#ifndef GAME_STATE_COMPONENT_HPP
#define GAME_STATE_COMPONENT_HPP

#include <vector>

namespace Components {
    struct GameStateComponent {
        std::vector<unsigned int> playerDrones;
        std::vector<unsigned int> playerEnergy;

        GameStateComponent(unsigned int playerCount) {
            playerDrones.resize(playerCount);
            playerEnergy.resize(playerCount);
        }
    };
}

#endif // GAME_STATE_COMPONENT_HPP