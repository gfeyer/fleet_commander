#ifndef POWER_PLANT_COMPONENT_HPP
#define POWER_PLANT_COMPONENT_HPP

#include <string>

namespace Components {
    struct PowerPlantComponent {
        std::string powerPlantName;
        unsigned int capacity = 0;

        PowerPlantComponent(const std::string& powerPlantName, unsigned int capacity) : powerPlantName(powerPlantName), capacity(capacity) {}
    };
}

 // TODO: Resource - only build drones up to maximum capacity
 // TODO: keep track in game object
 // TODO: display capacity and drones on GUI
#endif // POWER_PLANT_COMPONENT_HPP