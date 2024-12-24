#include "resource_manager.hpp"

#include "logger.hpp"

ResourceManager::ResourceManager() {
    log_trace << "CTOR ResourceManager::ResourceManager()";
}

ResourceManager::~ResourceManager() {
    log_trace << "DTOR ResourceManager::~ResourceManager()";
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance; // Singleton instance but allocate once on stack instead of heap, thread-safe
    return instance;
}

sf::Font& ResourceManager::getFont(const std::string& fontName) {
    ResourceManager& instance = ResourceManager::getInstance(); // Get reference to the instance

    auto it = instance.fonts.find(fontName);
    if (it == instance.fonts.end()) {
        // Load the font and insert into the map
        auto font = std::make_unique<sf::Font>();
        if (!font->loadFromFile(fontName)) {
            throw std::runtime_error("Failed to load font: " + fontName);
        }
        instance.fonts[fontName] = std::move(font);  // Insert the font
    }

    // Return the found or newly inserted font
    return *instance.fonts[fontName];
}

tgui::Theme::Ptr ResourceManager::getTheme(const std::string &themePath)
{
    ResourceManager& instance = ResourceManager::getInstance(); // Get reference to the instance

    if (instance.theme == nullptr) {
        instance.theme = tgui::Theme::create(themePath);
    }

    return instance.theme;
}
