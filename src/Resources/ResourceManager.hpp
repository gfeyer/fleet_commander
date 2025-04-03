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
    constexpr const char* BACKGROUND_4 = "assets/background/Background-4.png";

    // Themes
    constexpr const char* DARK_THEME = "assets/themes/Dark.txt";

    // Fonts
    constexpr const char* FONT_TOXIGENESIS = "assets/fonts/toxigenesis.otf";

    // Textures
    constexpr const char* TEXTURE_SPACE_EXTENSION = "assets/texture/extension.png";

    // Atlas
    constexpr const char* ATLAS_SPACE_EXTENSION = "assets/texture/extension.xml";
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

    const sf::Texture& getTexture(const char* path) const;
    const Atlas& getAtlas(const char* path) const;
    const tgui::Theme::Ptr getTheme(const char* path) const;
    const sf::Font& getFont(const char* path) const;
};

}


#endif