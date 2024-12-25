#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP

#include <SFML/Graphics.hpp>

namespace Components {
    struct TextComponent {
        sf::Text text;
        sf::Vector2f offset; // Relative position to the parent

        TextComponent() = default;

        TextComponent(const std::string& label, const sf::Font& font, unsigned int fontSize, const sf::Color& color, sf::Vector2f offset = {0.f, 0.f}) {
            text.setFont(font);
            text.setString(label);
            text.setCharacterSize(fontSize);
            text.setFillColor(color);
            this->offset = offset;
        }

        void setText(const std::string& label) {
            text.setString(label);
        }
    };
}

#endif // TEXT_COMPONENT_HPP