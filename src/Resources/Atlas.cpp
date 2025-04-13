#include "Atlas.hpp"
#include <cassert>
#include <fstream> // For file stream operations

#include <nlohmann/json.hpp>

#include "Utils/Logger.hpp"

using std::string;
using json = nlohmann::json;

Resource::Atlas::Atlas(AtlasFormat type, const string& path) {
    log_info << "Loading atlas: " << path;

    assert((type == AtlasFormat::XML || type == AtlasFormat::JSON) && "Atlas type not supported!");
    
    if(type == AtlasFormat::XML)
        parseXMLAtlas(path);
    else
        parseJSONAtlas(path);

        log_info << "Atlas parsed successfully: " << atlas.size() << " entries loaded.";
}

void Resource::Atlas::parseXMLAtlas(const std::string& xmlPath) {
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

void Resource::Atlas::parseJSONAtlas(const std::string &path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open atlas JSON: " + path);
    }

    json jsonData;
    try {
        // Read the entire file into the json object
        ifs >> jsonData;
    } catch (json::parse_error& e) {
        // Provide more specific error information
        throw std::runtime_error("Failed to parse atlas JSON: " + path + " - " + e.what() + " at byte " + std::to_string(e.byte));
    }
     // ifs automatically closed when it goes out of scope

    // --- Check JSON structure ---
    if (!jsonData.contains("frames") || !jsonData["frames"].is_object()) {
        throw std::runtime_error("Invalid JSON atlas format: Missing or non-object 'frames' key in " + path);
    }

    // Optional: Read metadata if needed
    // if (jsonData.contains("meta") && jsonData["meta"].is_object()) {
    //     const auto& meta = jsonData["meta"];
    //     if (meta.contains("image") && meta["image"].is_string()) {
    //         std::string textureFilename = meta["image"].get<std::string>();
    //         // Store or use textureFilename
    //     }
    // }

    // --- Iterate through frames ---
    const auto& frames = jsonData["frames"];
    for (auto it = frames.begin(); it != frames.end(); ++it) {
        const std::string& name = it.key(); // The filename (e.g., "bullet_2_blue.png")
        const json& frameData = it.value(); // The object containing frame details

        // Check for the mandatory "frame" object inside each entry
        if (!frameData.contains("frame") || !frameData["frame"].is_object()) {
            log_err << "Skipping invalid frame entry '" << name << "' in " << path << ": Missing or non-object 'frame' key.";
            continue;
        }

        const json& rectData = frameData["frame"];

        // Check for mandatory coordinate keys and ensure they are numbers
        if (!rectData.contains("x") || !rectData["x"].is_number() ||
            !rectData.contains("y") || !rectData["y"].is_number() ||
            !rectData.contains("w") || !rectData["w"].is_number() ||
            !rectData.contains("h") || !rectData["h"].is_number())
        {
            log_err << "Skipping invalid frame entry '" << name << "' in " << path << ": Missing or non-numeric coordinate in 'frame' object.";
            continue;
        }

        // Extract coordinates safely using get<int>()
        try {
            int x = rectData["x"].get<int>();
            int y = rectData["y"].get<int>();
            int w = rectData["w"].get<int>();
            int h = rectData["h"].get<int>();

            // Add the name and rectangle to the atlas map
            atlas[name] = sf::IntRect(x, y, w, h);
        } catch (json::type_error& e) {
            // Catch potential errors if data isn't exactly an integer (though is_number checks help)
             log_err << "Skipping frame entry '" << name << "' in " << path << ": Type error reading coordinates - " << e.what();
        }
    }
}

sf::IntRect Resource::Atlas::getRect(const string& name) const {
    auto it = atlas.find(name);
    if (it == atlas.end()) {
        log_err << "Atlas key not found: '" << name << "'";
        assert(!name.empty() && it != atlas.end() && "That name doesn't exist in the atlas!");
        // Return an empty rect or throw? Returning empty is potentially safer.
        return sf::IntRect();
    }
    // Use iterator instead of .at() to avoid double lookup
    return it->second;
}

sf::IntRect Resource::Atlas::getFrame(const string&, size_t idx) const {
    log_err << "Atlas::getFrame() is not implemented yet.";
    return sf::IntRect();
}
