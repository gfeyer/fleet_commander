#ifndef RESOURCE_ATLAS_HPP
#define RESOURCE_ATLAS_HPP

#include <map>

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

namespace Resource {

    class Atlas {
        public:
            Atlas(const std::string& path);
            sf::IntRect getRect(const std::string& name) const;
            sf::IntRect getFrame(const std::string& name, size_t idx) const; // animation

        private:
            void parseAtlas(const std::string& path);

        private:
            std::map<std::string, sf::IntRect> atlas;
    };
}


#endif // RESOURCE_ATLAS_HPP