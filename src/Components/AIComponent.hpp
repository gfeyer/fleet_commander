#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <set>

namespace Components {
    struct TargetIDPair{
        EntityID source;
        EntityID target;
        float cost = 0.f;

        // Define ordering for std::set
        bool operator<(const TargetIDPair& other) const {
            // Compare by cost first (ascending order)
            if (cost != other.cost) {
                return cost < other.cost;
            }
            // If costs are equal, compare by source and target
            return std::tie(source, target) < std::tie(other.source, other.target);
        }
    };

    struct AIPerception {
        unsigned int aiTotalDrones = 0;
        unsigned int aiTotalEnergy = 0;
        float aiDroneProductionRate = 0.f;
        std::set<TargetIDPair> aiAttackOrders;

        unsigned int playerTotalDrones = 0;
        unsigned int playerTotalEnergy = 0;
        float playerDroneProductionRate = 0.f;
        std::set<TargetIDPair> playerAttackOrders;

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

            aiAttackOrders.clear();
            playerAttackOrders.clear();
        }
    };

    struct AIPlan {
        std::string currentAction;

        void reset(){
        }
    };

    struct AIExecute {
        std::vector<TargetIDPair> finalTargets;

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