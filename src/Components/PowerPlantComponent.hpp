#ifndef POWER_PLANT_COMPONENT_HPP
#define POWER_PLANT_COMPONENT_HPP

#include <string>

namespace Components {
    struct PowerPlantComponent {
        std::string powerPlantName;
        unsigned int capacity = 0;

        PowerPlantComponent(const std::string& powerPlantName) : powerPlantName(powerPlantName) {}
    };
}

#endif // POWER_PLANT_COMPONENT_HPP