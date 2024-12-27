#ifndef HUD_SYSTEM_HPP
#define HUD_SYSTEM_HPP

#include <sstream>
#include <TGUI/TGUI.hpp>

#include "Core/Entity.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/TagComponent.hpp"
#include "Components/GarissonComponent.hpp"

#include "Config.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Systems {
    void HudSystem(std::unordered_map<EntityID, Entity>& entities, tgui::Gui& gui) {
        static tgui::Panel::Ptr infoPanel = nullptr;
        static tgui::Theme::Ptr theme = Resource::ResourceManager::getInstance().getTheme(Resource::Paths::DARK_THEME);

        if (!infoPanel) {
            infoPanel = tgui::Panel::create({"230", "150"});
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

                auto* factoryComp = entity.getComponent<Components::FactoryComponent>();
                auto* outpostComp = entity.getComponent<Components::OutpostComponent>();
                auto* garissonComp = entity.getComponent<Components::GarissonComponent>();
                auto* shieldComp = entity.getComponent<Components::ShieldComponent>();

                std::stringstream ss;

                if (factoryComp) {
                    ss << factoryComp->factoryName;
                    float productionRate = factoryComp->droneProductionRate;
                    float timeLeft = productionRate - factoryComp->productionTimer;

                    ss << "\nProduction rate: " << productionRate << " s\n";
                    
                    auto* factionComp = entity.getComponent<Components::FactionComponent>();
                    if(factionComp && factionComp->factionID != 0){ 
                        ss << "\nNext drone in: " << unsigned int(timeLeft) << " s";
                    }
                }

                if (outpostComp) {
                    ss << outpostComp->outpostName;
                }

                if(garissonComp){
                    ss << "\nDrones stationed: " << garissonComp->getDroneCount();
                }

                if(shieldComp){
                    ss << "\nShield: " << shieldComp->currentShield << "/" << shieldComp->maxShield;
                }

                auto label = tgui::Label::create(ss.str());
                label->setRenderer(theme->getRenderer("Label"));
                label->setTextSize(Config::GUI_TEXT_SIZE);
                infoPanel->add(label);

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