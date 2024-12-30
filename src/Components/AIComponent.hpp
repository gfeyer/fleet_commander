#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include <unordered_map>

namespace Components {
    struct AIPerception {
        unsigned int aiTotalDrones = 0;
        unsigned int aiTotalEnergy = 0;

        unsigned int playerTotalDrones = 0;
        unsigned int playerTotalEnergy = 0;
        sf::Vector2f aiCentralPosition;

        std::unordered_map<EntityID, unsigned int> garissonByDroneCount;
        std::unordered_map<EntityID, Components::Faction> garissonByFaction;

        void reset(){
            aiTotalDrones = 0;
            aiTotalEnergy = 0;
            playerTotalDrones = 0;
            playerTotalEnergy = 0;
            aiCentralPosition = {0.f, 0.f};

            garissonByDroneCount.clear();
            garissonByFaction.clear();

            
        }
    };

    struct AIPlan {
        std::string currentAction;
    };

    struct AIExecute {
        std::unordered_set<EntityID> selectedTargets;
    };

    struct AIDebug {
        float lastDecisionTime = 0.0f;
    };

    struct AIComponent {
        EntityID highlightedEntityID = 0;
        AIPerception perception;
        AIPlan plan;
        AIExecute execute;
        AIDebug debug;

        void reset() { 
            perception.reset(); 
        }
    };
}

#endif // AI_COMPONENT_HPP