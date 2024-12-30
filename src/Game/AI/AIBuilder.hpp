#ifndef AI_BUILDER_HPP
#define AI_BUILDER_HPP

#include <behaviortree_cpp/bt_factory.h>

#include "Utils/Logger.hpp"
namespace Game::AI {
    BT::Tree BuildBehaviorTree(){

        // Create a Behavior Tree Factory
        BT::BehaviorTreeFactory factory;

        // Register Nodes
        // TODO ...
        factory.registerSimpleAction("ReturnSuccess", [&](BT::TreeNode&){
            log_info << "Node: ReturnSuccess";
            return BT::NodeStatus::SUCCESS; 
        });

        auto tree = factory.createTreeFromFile("ai_balanced.xml");
        return tree;
    }
}

#endif // AI_BUILDER_HPP