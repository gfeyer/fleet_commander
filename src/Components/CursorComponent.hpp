#ifndef CURSOR_COMPONENT_HPP
#define CURSOR_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components
{
    enum class CursorType : unsigned int {
        NONE = 0,
        FRIENDLY = 1,
        ATTACK = 2,
    };

    struct CursorComponent
    {
        CursorType type = CursorType::NONE;
    };
} 



#endif // CURSOR_COMPONENT_HPP