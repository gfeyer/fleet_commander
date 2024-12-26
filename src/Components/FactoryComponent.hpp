#ifndef FACTORY_COMPONENT_HPP
#define FACTORY_COMPONENT_HPP

#include <string>
#include <unordered_set>

namespace Components {
    struct FactoryComponent {
        std::string factoryName;
        unsigned int stationedDrones = 0;        
        float droneProductionRate = 1.f;
        float productionTimer = 0.f;

        FactoryComponent(const std::string& factoryName) : factoryName(factoryName) {}
    };
}

#endif