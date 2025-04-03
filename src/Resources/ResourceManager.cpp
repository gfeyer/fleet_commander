#include "ResourceManager.hpp"

#include <memory>
#include <cassert>
#include "Atlas.hpp"
#include "Utils/Logger.hpp"

namespace Resource{

ResourceManager::ResourceManager() {
    log_info << "Loading assets";
    // loadTexture(Paths::BACKGROUND_4);
    loadTheme(Paths::DARK_THEME);
    loadFont(Paths::FONT_TOXIGENESIS);
    loadTexture(Paths::TEXTURE_SPACE_EXTENSION);
    loadAtlas(Paths::ATLAS_SPACE_EXTENSION);
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

void ResourceManager::loadAtlas(const char *path) {
    auto atlas = std::make_unique<Atlas>(path);
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

const sf::Texture& ResourceManager::getTexture(const char *path) const
{
    assert(path && *path != '\0' && textures.find(path) != textures.end() && "Texture not found");
    return *textures.at(path);
}

const Atlas &ResourceManager::getAtlas(const char *path) const 
{
    assert(path && *path != '\0' && atlases.find(path) != atlases.end() && "Atlas not found");
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