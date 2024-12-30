#ifndef AI_PERCEPTION_NODES_HPP
#define AI_PERCEPTION_NODES_HPP

#include <behaviortree_cpp/bt_factory.h>
#include "Utils/Logger.hpp"

#include "Game/GameEntityManager.hpp"

namespace Game::AI::Nodes {

    BT::NodeStatus CheckBattery(std::string tag)
    {
        log_info << "Battery: " << tag << " [ OK ]";
        return BT::NodeStatus::SUCCESS;
    }

}


#endif // AI_PERCEPTION_NODES_HPP