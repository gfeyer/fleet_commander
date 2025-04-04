#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "TGUI/TGUI.hpp"

#include "Atlas.hpp"

namespace Resource::Paths{
    // Textures
    constexpr const char* BACKGROUND = "assets/texture/background.png";

    // Themes
    constexpr const char* DARK_THEME = "assets/themes/Dark.txt";

    // Fonts
    constexpr const char* FONT_TOXIGENESIS = "assets/fonts/toxigenesis.otf";

    // Individual textures
    constexpr const char* TEXTURE_FACTORY_RED = "assets/texture/factory.png";
    // constexpr const char* TEXTURE_FACTORY_BLUE = "assets/texture/factory.png";

    constexpr const char* TEXTURE_DRONE_RED = "assets/texture/drone.png";
    // constexpr const char* TEXTURE_DRONE_BLUE = "assets/texture/drone.png";

    constexpr const char* TEXTURE_POWER_STATION_RED = "assets/texture/powerstation.png";
    // constexpr const char* TEXTURE_POWER_PLANT_BLUE = "assets/texture/power_blue.png";
}


namespace Resource{

class ResourceManager {
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::map<std::string, std::unique_ptr<Atlas>> atlases;
    std::map<std::string, tgui::Theme::Ptr> themes;
    std::map<std::string, std::unique_ptr<sf::Font>> fonts;

private:
    ResourceManager();  // Private constructor
    ~ResourceManager();

    void loadTexture(const char* path);
    void loadAtlas(const char* path);
    void loadTheme(const char* path);
    void loadFont(const char* path);

public:
    // Get the singleton instance
    static ResourceManager& getInstance();

    const sf::Texture& getTexture(const std::string& path) const;
    const Atlas& getAtlas(const std::string& path) const;
    const tgui::Theme::Ptr getTheme(const char* path) const;
    const sf::Font& getFont(const char* path) const;
};

}


#endif