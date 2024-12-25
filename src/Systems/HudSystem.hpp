#ifndef HUD_SYSTEM_HPP
#define HUD_SYSTEM_HPP

#include <TGUI/TGUI.hpp>

#include "Core/Entity.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/TagComponent.hpp"

#include "Config.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Systems {
    void HudSystem(std::unordered_map<int, Entity>& entities, tgui::Gui& gui) {
        static tgui::Panel::Ptr infoPanel = nullptr;
        static tgui::Theme::Ptr theme = Resource::ResourceManager::getInstance().getTheme(Resource::Paths::DARK_THEME);

        if (!infoPanel) {
            infoPanel = tgui::Panel::create({"200", "100"});
            infoPanel->setVisible(false);
            infoPanel->setRenderer(theme->getRenderer("Panel"));
            gui.add(infoPanel);
        }

        bool entityHovered = false;

        for (auto& [id, entity] : entities) {
            auto* hoverComp = entity.getComponent<Components::HoverComponent>();
            auto* tagComponent = entity.getComponent<Components::TagComponent>();

            if (hoverComp && hoverComp->isHovered) {
                entityHovered = true;
                infoPanel->setVisible(true);
                infoPanel->setRenderer(theme->getRenderer("Panel"));
                infoPanel->removeAllWidgets();

                if (tagComponent) {
                    auto label = tgui::Label::create("Info\n" + tagComponent->tag);
                    label->setRenderer(theme->getRenderer("Label"));
                    label->setTextSize(Config::GUI_TEXT_SIZE);
                    infoPanel->add(label);
                }

                infoPanel->setPosition({hoverComp->position.x, hoverComp->position.y});
                break; // Show info for the first hovered entity only
            }
        }

        if (!entityHovered) {
            infoPanel->setVisible(false);
        }
    }
}



#endif // HUD_SYSTEM_HPP