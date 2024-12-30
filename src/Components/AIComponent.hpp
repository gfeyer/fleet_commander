#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>

namespace Components {
    struct EntityIDPair{
        EntityID source;
        EntityID target;
    };

    struct AIPerception {
        unsigned int aiTotalDrones = 0;
        unsigned int aiTotalEnergy = 0;
        float aiDroneProductionRate = 0.f;

        unsigned int playerTotalDrones = 0;
        unsigned int playerTotalEnergy = 0;
        float playerDroneProductionRate = 0.f;

        sf::Vector2f aiCentralPosition;

        std::unordered_map<EntityID, unsigned int> garissonByDroneCount;
        std::unordered_map<EntityID, std::map<float, EntityID>> garissonsByDistance;
        std::unordered_set<EntityID> playerGarissons;
        std::unordered_set<EntityID> aiGarissons;

        void reset(){
            aiTotalDrones = 0;
            aiTotalEnergy = 0;
            aiDroneProductionRate = 0.f;

            playerTotalDrones = 0;
            playerTotalEnergy = 0;
            playerDroneProductionRate = 0.f;

            aiCentralPosition = {0.f, 0.f};

            garissonByDroneCount.clear();
            garissonsByDistance.clear();

            playerGarissons.clear();
            aiGarissons.clear();
        }
    };

    struct AIPlan {
        std::string currentAction;
        std::map<float, EntityIDPair> potentialSingleAttackTargetsByDistance; 

        void reset(){
            potentialSingleAttackTargetsByDistance.clear();
        }
    };

    struct AIExecute {
        std::vector<EntityIDPair> finalTargets;

        void reset() { finalTargets.clear(); }
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
            execute.reset();
            debug.reset();
        }
    };
}

#endif // AI_COMPONENT_HPP