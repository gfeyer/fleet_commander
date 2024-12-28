#ifndef HUD_SYSTEM_HPP
#define HUD_SYSTEM_HPP

#include <sstream>
#include <TGUI/TGUI.hpp>
#include <cstdio>

#include "Core/Entity.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/TagComponent.hpp"
#include "Components/GarissonComponent.hpp"
#include "Components/FactionComponent.hpp"

#include "Config.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Systems {
    void HudSystem(Game::GameEntityManager& entityManager, tgui::Gui& gui) {
        static tgui::Theme::Ptr theme = Resource::ResourceManager::getInstance().getTheme(Resource::Paths::DARK_THEME);

        // GUI widgets declarations
        static tgui::Panel::Ptr infoPanel = nullptr;
        static tgui::Panel::Ptr topPanel = nullptr;
        static tgui::Label::Ptr player1Label = nullptr;
        static tgui::Label::Ptr player2Label = nullptr;
        
        // Panels Init
        if (!infoPanel) {
            infoPanel = tgui::Panel::create({"230", "180"});
            infoPanel->setVisible(false);
            infoPanel->setRenderer(theme->getRenderer("Panel"));
            gui.add(infoPanel);
        }

        if(!topPanel) {
            topPanel = tgui::Panel::create({"100%", "100"}); // Full width, fixed height
            topPanel->setRenderer(theme->getRenderer("Panel"));
            gui.add(topPanel);

            // Add Player 1 Label (Left-Aligned)
            player1Label = tgui::Label::create();
            player1Label->setRenderer(theme->getRenderer("Label"));
            player1Label->setTextSize(Config::GUI_TEXT_SIZE);
            player1Label->setPosition({"10", "10"}); // Small offset from top-left
            topPanel->add(player1Label);

            // Add Player 2 Label (Right-Aligned)
            player2Label = tgui::Label::create();
            player2Label->setRenderer(theme->getRenderer("Label"));
            player2Label->setTextSize(Config::GUI_TEXT_SIZE);
            player2Label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
            player2Label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
            player2Label->setSize({"50%", "100%"}); // Occupy 50% of the panel width
            player2Label->setPosition({"50%", "0"}); // Start at the middle of the panel
            topPanel->add(player2Label);
        }

        // Top Panel display logic
        auto* gameState = entityManager.getGameStateEntity().getComponent<Components::GameStateComponent>();
        if (gameState)
        {
            auto totalPlayers = gameState->playerDrones.size();

            if(totalPlayers == 0){
                throw std::runtime_error("No players found");
            }

            if (totalPlayers > 0)
            {
                std::stringstream ss;
                ss << "Player 1";
                ss << "\nDrones: " << gameState->playerDrones[Components::Faction::PLAYER_1];
                auto playerDrones = gameState->playerDrones[Components::Faction::PLAYER_1];
                auto playerEnergy = gameState->playerEnergy[Components::Faction::PLAYER_1];

                if(playerEnergy <= playerDrones){
                    ss << " [production blocked]";
                }

                ss << "\nEnergy: " << gameState->playerEnergy[Components::Faction::PLAYER_1];
                player1Label->setText(ss.str());
            }

            if(totalPlayers > 1){
                std::stringstream ss;
                ss << "Player 2";
                auto playerDrones = gameState->playerDrones[Components::Faction::PLAYER_2];
                auto playerEnergy = gameState->playerEnergy[Components::Faction::PLAYER_2];

                ss << "\n";
                if(playerEnergy <= playerDrones){
                    ss << " [production blocked] ";
                }
                ss << "Drones: " << gameState->playerDrones[Components::Faction::PLAYER_2];


                ss << "\nEnergy: " << gameState->playerEnergy[Components::Faction::PLAYER_2];
                player2Label->setText(ss.str());
            }
        }
        
        // Hover Panel display logic
        bool entityHovered = false;
        auto& entities = entityManager.getAllEntities();
        for (auto& [id, entity] : entities) {

            auto* hoverComp = entity.getComponent<Components::HoverComponent>();
            auto* tagComponent = entity.getComponent<Components::TagComponent>();

            if (hoverComp && hoverComp->isHovered) {
                entityHovered = true;
                infoPanel->setVisible(true);
                infoPanel->setRenderer(theme->getRenderer("Panel"));
                infoPanel->removeAllWidgets();

                auto* factoryComp = entity.getComponent<Components::FactoryComponent>();
                auto* powerPlantComp = entity.getComponent<Components::PowerPlantComponent>();
                auto* garissonComp = entity.getComponent<Components::GarissonComponent>();
                auto* shieldComp = entity.getComponent<Components::ShieldComponent>();

                std::stringstream ss;

                if (factoryComp) {
                    ss << factoryComp->factoryName;

                    float productionRate = factoryComp->droneProductionRate;

                    // Format Production Rate and Time Left
                    char buffer[100];
                    std::snprintf(
                        buffer, 
                        sizeof(buffer), 
                        "\nProduction rate: %.1f /s", 
                        productionRate
                    );
                    ss << buffer;
                }

                if (powerPlantComp) {
                    ss << "FusionReactor\nCapacity: " << powerPlantComp->capacity;
                }

                if(garissonComp){
                    ss << "\nDrones stationed: " << garissonComp->getDroneCount();
                }

                if(shieldComp){
                    // Format Shield values
                    char buffer[100];
                    std::snprintf(
                        buffer, 
                        sizeof(buffer), 
                        "\nShield: %.1f/%.1f\nShield Regen: %.1f/s", 
                        shieldComp->currentShield, 
                        shieldComp->maxShield, 
                        shieldComp->regenRate
                    );
                    ss << buffer;
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