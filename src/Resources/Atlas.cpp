#include "Atlas.hpp"
#include <cassert>

#include "Utils/Logger.hpp"

using std::string;

Resource::Atlas::Atlas(const string& path) {
    log_info << "Loading atlas: " << path;
    parseAtlas(path);
    log_info << "Atlas parsed successfully";
}

void Resource::Atlas::parseAtlas(const std::string& xmlPath) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xmlPath.c_str()) != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error("Failed to load atlas XML: " + xmlPath);
    }

    auto* root = doc.FirstChildElement("TextureAtlas");
    if (!root) throw std::runtime_error("Missing <TextureAtlas> root element");

    for (auto* subTex = root->FirstChildElement("SubTexture"); subTex; subTex = subTex->NextSiblingElement("SubTexture")) {
        const char* name = subTex->Attribute("name");
        int x = subTex->IntAttribute("x");
        int y = subTex->IntAttribute("y");
        int w = subTex->IntAttribute("width");
        int h = subTex->IntAttribute("height");

        if (name) {
            atlas[name] = sf::IntRect(x, y, w, h);
        }
    }
}

sf::IntRect Resource::Atlas::getRect(const string& name) const {
    assert(!name.empty() && atlas.find(name) != atlas.end() && "That name doesn't exist in the atlas!");
    return atlas.at(name);
}

sf::IntRect Resource::Atlas::getFrame(const string&, size_t idx) const {
    return sf::IntRect();
}
