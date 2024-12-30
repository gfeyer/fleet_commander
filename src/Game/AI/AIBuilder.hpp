#ifndef AI_BUILDER_HPP
#define AI_BUILDER_HPP

#include <behaviortree_cpp/bt_factory.h>
#include "Utils/Logger.hpp"

#include "Game/AI/AIPerceptionNodes.hpp"
#include "Game/GameEntityManager.hpp"

namespace Game::AI {
    BT::Tree BuildBehaviorTree(){

        // Create a Behavior Tree Factory
        BT::BehaviorTreeFactory factory;

        // Register Nodes
        // TODO ...
        factory.registerSimpleAction("CheckBattery", [&](BT::TreeNode&){ 
            log_info << "Battery: A [ OK ]"; 
            return Game::AI::Nodes::CheckBattery("AAA");
        });

        auto tree = factory.createTreeFromFile("ai_balanced.xml");
        return tree;
    }
}

#endif // AI_BUILDER_HPP