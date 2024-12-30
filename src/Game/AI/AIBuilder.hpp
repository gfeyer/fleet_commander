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
        factory.registerSimpleAction("CheckBattery", [&](BT::TreeNode&){ return BT::NodeStatus::SUCCESS; });

        log_info << "Creating Behavior Tree";
        auto tree = factory.createTreeFromFile("behaviortree_balanced.xml");
        log_info << "Finished Behavior Tree";
        return tree;
    }
}

#endif // AI_BUILDER_HPP