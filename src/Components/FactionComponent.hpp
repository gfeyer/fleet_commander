#ifndef FACTION_COMPONENT_HPP
#define FACTION_COMPONENT_HPP

#include <string> 

#include <sfml/Graphics.hpp>

namespace Components {
    enum class Faction : unsigned int {
        NEUTRAL = 0,
        PLAYER_1 = 1,
        PLAYER_2 = 2,
        PLAYER_3 = 3
    };

    struct FactionComponent {
        Faction faction = Faction::NEUTRAL;
        FactionComponent(Faction id = Faction::NEUTRAL) : faction(id) {}
    };
}

#endif