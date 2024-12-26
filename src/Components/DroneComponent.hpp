#ifndef DRONE_COMPONENT_HPP
#define DRONE_COMPONENT_HPP

#include <string>
#include "Utils/Logger.hpp"

namespace Components {
    struct DroneComponent {
        std::string droneName;

        DroneComponent(const std::string& droneName) : droneName(droneName) {}
        ~DroneComponent(){log_info << "Destroying Drone " << droneName;};
    };
}

#endif