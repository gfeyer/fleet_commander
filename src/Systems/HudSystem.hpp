#ifndef HUD_SYSTEM_HPP
#define HUD_SYSTEM_HPP

#include <sstream>
#include <TGUI/TGUI.hpp>
#include <cstdio>


#include "Components/HoverComponent.hpp"
#include "Components/TagComponent.hpp"
#include "Components/GarissonComponent.hpp"
#include "Components/FactionComponent.hpp"

#include "Config.hpp"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Systems {
    void HudSystem(Game::GameEntityManager& manager, tgui::Gui& gui) {
        static tgui::Theme::Ptr theme = Resource::ResourceManager::getInstance().getTheme(Resource::Paths::DARK_THEME);

        // GUI widgets declarations
        static tgui::Panel::Ptr infoPanel = nullptr;
        static tgui::Panel::Ptr topPanel = nullptr;
        static tgui::Panel::Ptr gameOverPanel = nullptr;
        static tgui::Label::Ptr fpsLabel = nullptr;


        // Top screen labels
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

            // Add AI Difficulty Label
            auto difficultyLabel = tgui::Label::create("AI Difficulty:");
            difficultyLabel->setRenderer(theme->getRenderer("Label"));
            difficultyLabel->setTextSize(Config::GUI_TEXT_SIZE);
            difficultyLabel->setPosition({"55%", "10"});
            topPanel->add(difficultyLabel);

            // Add AI Difficulty ComboBox
            auto difficultyComboBox = tgui::ComboBox::create();
            difficultyComboBox->setRenderer(theme->getRenderer("ComboBox"));
            difficultyComboBox->setSize({"20%", "50%"}); // Adjust width and height
            difficultyComboBox->setPosition({"55%", "40"}); // Position under the label
            difficultyComboBox->setTextSize(Config::GUI_TEXT_SIZE - 2);

            // Add difficulty levels
            difficultyComboBox->addItem("Easy");
            difficultyComboBox->addItem("Medium");
            difficultyComboBox->addItem("Hard");
            difficultyComboBox->addItem("Impossible");

            // Default selection
            difficultyComboBox->setSelectedItem("Medium");

            // Handle selection change
            difficultyComboBox->onItemSelect([&](const tgui::String& item){
                auto difficulty = item.toStdString();
                log_info << "AI Difficulty: " << difficulty;
                if(difficulty == "Easy"){
                    Config::Difficulty::AI_DECISION_INTERVAL_SEC = 10.f;
                    Config::Difficulty::AI_MAX_EXECUTIONS_PER_TURN = 2;
                    Config::Difficulty::AI_MAX_DISTANCE_TO_ATTACK = 300.f;
                }else if(difficulty == "Medium"){
                    Config::Difficulty::AI_DECISION_INTERVAL_SEC = 5.f;
                    Config::Difficulty::AI_MAX_EXECUTIONS_PER_TURN = 10;
                    Config::Difficulty::AI_MAX_DISTANCE_TO_ATTACK = 500.f;
                }else if(difficulty == "Hard"){
                    Config::Difficulty::AI_DECISION_INTERVAL_SEC = 3.f;
                    Config::Difficulty::AI_MAX_EXECUTIONS_PER_TURN = 15;
                    Config::Difficulty::AI_MAX_DISTANCE_TO_ATTACK = 750.f;
                }else if(difficulty == "Impossible"){
                    Config::Difficulty::AI_DECISION_INTERVAL_SEC = 1.f;
                    Config::Difficulty::AI_MAX_EXECUTIONS_PER_TURN = 30;
                    Config::Difficulty::AI_MAX_DISTANCE_TO_ATTACK = 2000.f;
                }
            });

            // Add ComboBox to the panel
            topPanel->add(difficultyComboBox, "difficultyComboBox");

        }

        // Top Panel display logic
        auto* gameState = manager.getGameStateComponent();
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
        for (auto&& [id, hover] : manager.view<Components::HoverComponent>().each()) {

            if (hover.isHovered) {
                entityHovered = true;
                infoPanel->setVisible(true);
                infoPanel->setRenderer(theme->getRenderer("Panel"));
                infoPanel->removeAllWidgets();

                auto* factoryComp = manager.getComponent<Components::FactoryComponent>(id);
                auto* powerPlantComp = manager.getComponent<Components::PowerPlantComponent>(id);
                auto* garissonComp = manager.getComponent<Components::GarissonComponent>(id);
                auto* shieldComp = manager.getComponent<Components::ShieldComponent>(id);

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

                infoPanel->setPosition({hover.position.x, hover.position.y});
                break; // Show info for the first hovered entity only
            }
        }

        if (!entityHovered) {
            infoPanel->setVisible(false);
        }

        // Game Over Panel - initialization
        if (!gameOverPanel) {
            gameOverPanel = tgui::Panel::create({"400", "200"}); // Larger panel for game over text
            gameOverPanel->setVisible(false); // Hidden by default
            gameOverPanel->setRenderer(theme->getRenderer("Panel"));
            gameOverPanel->setPosition({"50%", "40%"}); // Centered on screen
            gameOverPanel->setOrigin(0.5f, 0.5f);

            auto gameOverLabel = tgui::Label::create();
            gameOverLabel->setTextSize(24);
            gameOverLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
            gameOverLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
            gameOverLabel->setRenderer(theme->getRenderer("Label"));
            gameOverLabel->setPosition({"50%", "50%"});
            gameOverLabel->setOrigin(0.5f, 0.5f);

            gameOverPanel->add(gameOverLabel, "GameOverLabel");

            gui.add(gameOverPanel);
        }

        if(gameState && gameState->isGameOver){
            auto gameOverLabel = gameOverPanel->get<tgui::Label>("GameOverLabel");
    
            if (gameState->winner == Components::Faction::PLAYER_1) {
                gameOverLabel->setText("🎉 YOU WIN! 🎉");
                gameOverLabel->getRenderer()->setTextColor(tgui::Color::Green);
            } else if (gameState->winner == Components::Faction::PLAYER_2) {
                gameOverLabel->setText("💀 YOU LOSE! 💀");
                gameOverLabel->getRenderer()->setTextColor(tgui::Color::Red);
            } else {
                gameOverLabel->setText("🏁 GAME OVER 🏁");
                gameOverLabel->getRenderer()->setTextColor(tgui::Color::White);
            }

            gameOverPanel->setVisible(true);
        }else{
            gameOverPanel->setVisible(false);
        }


        if(!fpsLabel){
            // Add FPS Label (Lower-Right Corner)
            fpsLabel = tgui::Label::create();
            fpsLabel->setRenderer(theme->getRenderer("Label"));
            fpsLabel->setTextSize(Config::GUI_TEXT_SIZE);
            fpsLabel->setPosition({"100% - 150", "100% - 40"}); // Offset from bottom-right corner
            fpsLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
            fpsLabel->setVerticalAlignment(tgui::Label::VerticalAlignment::Bottom);
            fpsLabel->setVisible(false);
            gui.add(fpsLabel);
        }

        for(auto&& [id, debug] : manager.view<Components::DebugOverlayComponent>().each()) {
            fpsLabel->setText("FPS: " + std::to_string(debug.fps));
            fpsLabel->setVisible(true);
        }
    }
}

#endif // HUD_SYSTEM_HPP