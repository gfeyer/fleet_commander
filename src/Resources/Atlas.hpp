#ifndef RESOURCE_ATLAS_HPP
#define RESOURCE_ATLAS_HPP

#include <map>

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

namespace Resource {

    enum class AtlasFormat {
        XML,
        JSON
    };

    class Atlas {
        public:
            Atlas(AtlasFormat format, const std::string& path);
            sf::IntRect getRect(const std::string& name) const;
            sf::IntRect getFrame(const std::string& name, size_t idx) const; // animation

        private:
            void parseXMLAtlas(const std::string& path);
            void parseJSONAtlas(const std::string& path);

        private:
            std::map<std::string, sf::IntRect> atlas;
    };
}


#endif // RESOURCE_ATLAS_HPP