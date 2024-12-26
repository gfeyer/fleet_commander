#ifndef OUTPOST_COMPONENT_HPP
#define OUTPOST_COMPONENT_HPP

#include <string>

namespace Components {
    struct OutpostComponent {
        std::string outpostName;

        OutpostComponent(const std::string& outpostName) : outpostName(outpostName) {}
    };
}

#endif // OUTPOST_COMPONENT_HPP