#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>

namespace Components {
    struct AIPerception {
        unsigned int aiTotalDrones = 0;
        unsigned int aiTotalEnergy = 0;

        unsigned int playerTotalDrones = 0;
        unsigned int playerTotalEnergy = 0;
        sf::Vector2f aiCentralPosition;

        std::unordered_map<EntityID, unsigned int> garissonByDroneCount;
        std::unordered_map<EntityID, std::map<float, EntityID>> garissonsByDistance;
        std::unordered_set<EntityID> playerGarissons;
        std::unordered_set<EntityID> aiGarissons;

        void reset(){
            aiTotalDrones = 0;
            aiTotalEnergy = 0;
            playerTotalDrones = 0;
            playerTotalEnergy = 0;
            aiCentralPosition = {0.f, 0.f};

            garissonByDroneCount.clear();
            garissonsByDistance.clear();

            playerGarissons.clear();
            aiGarissons.clear();
        }
    };

    struct AIPlan {
        std::string currentAction;
        std::unordered_map<EntityID, EntityID> potentialAttackTargets; 

        void reset(){
            potentialAttackTargets.clear();
        }
    };

    struct AIExecute {
        std::unordered_set<EntityID> selectedTargets;
    };

    struct AIDebug {
        std::vector<sf::Vector2f> yellowDebugTargets;
        std::vector<sf::Vector2f> pinkDebugTargets;

        void reset() { 
            yellowDebugTargets.clear();
            pinkDebugTargets.clear(); 
        }
    };

    struct AIComponent {
        EntityID highlightedEntityID = 0;
        AIPerception perception;
        AIPlan plan;
        AIExecute execute;
        AIDebug debug;

        void reset() { 
            perception.reset();
            plan.reset();
            debug.reset();
        }
    };
}

#endif // AI_COMPONENT_HPP