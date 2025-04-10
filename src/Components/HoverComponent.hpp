#ifndef HOVER_COMPONENT_HPP
#define HOVER_COMPONENT_HPP

namespace Components {

    struct HoverableComponent{
    };

    struct HoveredComponent{
        sf::Vector2f position = {0.f, 0.f};
    };
}

#endif  // HOVER_COMPONENT_HPP