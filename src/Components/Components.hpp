#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <sfml/System.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

namespace Components {

    // TODO: these turned out to be useles... to be deleted
    struct FactoryComponent {
        std::string factoryName;

        FactoryComponent(const std::string& factoryName) : factoryName(factoryName) {}
    };

    struct OutpostComponent {
        std::string outpostName;

        OutpostComponent(const std::string& outpostName) : outpostName(outpostName) {}
    };

    struct DroneComponent {
        std::string droneName;

        DroneComponent(const std::string& droneName) : droneName(droneName) {}
    };

}
#endif // COMPONENTS_HPP