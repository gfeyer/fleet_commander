#include "ResourceManager.hpp"

#include <memory>
#include <cassert>
#include "Atlas.hpp"
#include "Utils/Logger.hpp"

namespace Resource{

ResourceManager::ResourceManager() {
    log_info << "Loading assets";
    loadTexture(Paths::BACKGROUND);
    loadTheme(Paths::DARK_THEME);
    loadFont(Paths::FONT_TOXIGENESIS);

    // Individual textures
    loadTexture(Paths::TEXTURE_FACTORY);
    loadTexture(Paths::TEXTURE_FACTORY_RED);
    loadTexture(Paths::TEXTURE_FACTORY_BLUE);

    loadTexture(Paths::TEXTURE_POWER_STATION);
    loadTexture(Paths::TEXTURE_POWER_STATION_RED);
    loadTexture(Paths::TEXTURE_POWER_STATION_BLUE);

    loadTexture(Paths::TEXTURE_DRONE_RED);
    loadTexture(Paths::TEXTURE_DRONE_BLUE);

    loadTexture(Paths::TEXTURE_SHIELD);

    loadTexture(Paths::TEXTURE_POINTER_SELECT);
    loadTexture(Paths::TEXTURE_POINTER_TARGET);

    // Load atlas
    loadAtlas(AtlasFormat::JSON, Paths::EXPLOSIONS_ATLAS);
    loadTexture(Paths::TEXTURE_EXPLOSIONS_ATLAS);
}

ResourceManager::~ResourceManager() {
    log_info << "Unloading assets";
}

void ResourceManager::loadTexture(const char *path)
{
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(path)) {
        log_err << "Failed to load texture: " << path << std::endl;
    }
    textures.insert_or_assign(path, std::move(texture));
}

void ResourceManager::loadAtlas(AtlasFormat type, const char *path) {
    auto atlas = std::make_unique<Atlas>(type, path);
    atlases.insert_or_assign(path, std::move(atlas));
}

void ResourceManager::loadTheme(const char *path)
{
    auto theme = tgui::Theme::create(path);
    themes.insert_or_assign(path, theme);
}

void ResourceManager::loadFont(const char *path)
{
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(path)) {
        log_err << "Failed to load font: " << path << std::endl;
    }
    fonts.insert_or_assign(path, std::move(font));
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance; // Singleton instance but allocate once on stack instead of heap, thread-safe
    return instance;
}

const sf::Texture& ResourceManager::getTexture(const std::string& path) const
{
    assert(!path.empty() && textures.find(path) != textures.end() && "Texture not found");
    return *textures.at(path);
}

const Atlas &ResourceManager::getAtlas(const std::string& path) const 
{
    assert(!path.empty() && atlases.find(path) != atlases.end() && "Atlas not found");
    return *atlases.at(path);
}

const tgui::Theme::Ptr ResourceManager::getTheme(const char *path) const
{
    return themes.at(path);
}

const sf::Font& ResourceManager::getFont(const char *path) const
{
    return *fonts.at(path);
}


} // End namespace Resource