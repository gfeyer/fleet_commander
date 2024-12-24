#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "TGUI/TGUI.hpp"

class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;
    tgui::Theme::Ptr theme;
    ResourceManager();  // Private constructor
    ~ResourceManager();

public:
    // Get the singleton instance
    static ResourceManager& getInstance();

    // Load and retrieve a font by name
    static sf::Font& getFont(const std::string& fontName);

    // Load and retrieve a theme by name
    static tgui::Theme::Ptr getTheme(const std::string& themeName);

};

#endif