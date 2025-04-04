#ifndef COMPONENTS_UNIT_TYPE_COMPONENT_HPP
#define COMPONENTS_UNIT_TYPE_COMPONENT_HPP

namespace Components {
    enum class UnitType { PowerPlant, Factory, Drone };

    struct UnitTypeComponent {
        UnitType type;
    };
}

#endif // COMPONENTS_UNIT_TYPE_COMPONENT_HPP