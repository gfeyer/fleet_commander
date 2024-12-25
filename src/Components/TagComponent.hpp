#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string>
namespace Components {

    struct TagComponent {
        std::string tag;
        TagComponent(const std::string& tag) : tag(tag) {}
    };
}

#endif // TAG_COMPONENT_HPP