#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include <behaviortree_cpp/bt_factory.h>
#include "Game/GameEntityManager.hpp"

namespace Components {
    struct AIComponent {
        BT::Tree AITree;
        EntityID highlightedEntityID = 0;

        AIComponent(BT::Tree&& tree) : AITree(std::move(tree)) {}
    };
}

#endif // AI_COMPONENT_HPP