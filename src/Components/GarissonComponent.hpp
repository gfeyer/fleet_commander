#ifndef GARISSON_COMPONENT_HPP
#define GARISSON_COMPONENT_HPP

namespace Components {
    struct GarissonComponent {
        unsigned int droneCount = 0;

        void setDroneCount(unsigned int count) { droneCount = count; }
        void incrementDroneCount() { droneCount++; }
        unsigned int getDroneCount() const { return droneCount; }
    };
}

#endif // GARISSON_COMPONENT_HPP