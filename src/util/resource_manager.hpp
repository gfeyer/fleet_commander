#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;
    ResourceManager();  // Private constructor
    ~ResourceManager();

public:
    // Get the singleton instance
    static ResourceManager& getInstance();

    // Load and retrieve a font by name
    static sf::Font& getFont(const std::string& fontName);


};

#endif