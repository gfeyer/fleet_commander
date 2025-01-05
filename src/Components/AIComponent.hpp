#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <set>

using EntityID = entt::entity;

namespace Components {

    namespace AI{
        struct AttackPair{
                EntityID source;
                EntityID target;
                float distance = 0.f;
                float cost = 0.f;

                AttackPair(EntityID source, EntityID target, float dist, float cost) : source(source), target(target), distance(dist), cost(cost) {}
            };

            // Comparator for Cost
            struct ComparatorPairByCost {
                bool operator()(const AttackPair& a, const AttackPair& b) const {
                    if (a.cost != b.cost) {
                        return a.cost < b.cost;
                    }
                    return std::tie(a.source, a.target) < std::tie(b.source, b.target);
                }
            };

            // Comparator for Distance
            struct ComparatorPairByDistance {
                bool operator()(const AttackPair& a, const AttackPair& b) const {
                    if (a.distance != b.distance) {
                        return a.distance < b.distance;
                    }
                    return std::tie(a.source, a.target) < std::tie(b.source, b.target);
                }
            };
    }
    
    struct AIPerception {
        unsigned int aiTotalDrones = 0;
        unsigned int aiTotalEnergy = 0;
        float aiDroneProductionRate = 0.f;
        std::set<AI::AttackPair, AI::ComparatorPairByDistance> aiAttackOrders;

        unsigned int playerTotalDrones = 0;
        unsigned int playerTotalEnergy = 0;
        float playerDroneProductionRate = 0.f;
        std::set<AI::AttackPair, AI::ComparatorPairByDistance> playerAttackOrders;

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
        std::vector<Components::AI::AttackPair> finalTargets;

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
        EntityID highlightedEntityID;
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