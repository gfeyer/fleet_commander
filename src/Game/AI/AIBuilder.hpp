#ifndef AI_BUILDER_HPP
#define AI_BUILDER_HPP

#include <behaviortree_cpp/bt_factory.h>

namespace Game::AI {
    BT::Tree BuildBehaviorTree(){

        // Create a Behavior Tree Factory
        BT::BehaviorTreeFactory factory;

        // Register Nodes
        // TODO ...

        auto tree = factory.createTreeFromFile("balanced_behavior.xml");

        return tree;
    }
}

#endif // AI_BUILDER_HPP