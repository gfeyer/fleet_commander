#include "Scene.hpp"

#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"

#include "Utils/Logger.hpp"
#include "Resources/ResourceManager.hpp"
#include "Config.hpp"

#include "Components/FactionComponent.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/PowerPlantComponent.hpp"
#include "Components/DroneComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/TagComponent.hpp"
#include "Components/HoverComponent.hpp"
#include "Components/GameStateComponent.hpp"
#include "Components/AIComponent.hpp"
#include <Components/DebugOverlayComponent.hpp>

#include "Systems/MovementSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/LabelUpdateSystem.hpp"
#include "Systems/InputSelectionSystem.hpp"
#include "Systems/InputHoverSystem.hpp"
#include "Systems/HudSystem.hpp"
#include "Systems/ProductionSystem.hpp"
#include "Systems/CombatSystem.hpp"
#include "Systems/ShieldSystem.hpp"
#include "Systems/AI/AISystem.hpp"
#include "Systems/GameStateSystem.hpp"
#include "Systems/DroneTransferSystem.hpp"
#include "Systems/DebugOverlaySystem.hpp"
#include "Systems/SpriteUpdateSystem.hpp"

#include "Game/Builder.hpp"
#include "Game/MapGenerator.hpp"

#include "Utils/Random.hpp"

Scene::Scene(sf::RenderWindow& window) : windowRef(window)
{
    log_info << "Creating Scene";

    camera = sf::View(sf::FloatRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT));
    cameraPosition = sf::Vector2f(Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2); // Start at center

    // Initialize GUI
    gui = std::make_unique<tgui::Gui>(window);
    gui->setFont("assets/fonts/toxigenesis.otf"); // todo: move this to resource manager
    gui->setOpacity(0.9f);

    // Create Background Entity
    // Entity background;
    // auto backgroundEntityID = entityManager.createEntity();

    // auto& texture = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::BACKGROUND_4);
    // entityManager.addComponent(backgroundEntityID,Components::SpriteComponent{texture});
    // sf::Vector2u windowSize = sf::Vector2u(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    // sf::Vector2u textureSize = texture.getSize();
    // entityManager.addComponent(
    //     backgroundEntityID,
    //     Components::TransformComponent{
    //         sf::Vector2f(0, 0),
    //         0.f,
    //         sf::Vector2f(
    //             static_cast<float>(windowSize.x) / textureSize.x,
    //             static_cast<float>(windowSize.y) / textureSize.y
    //         )
    //     }
    // );

    // Create Game State Entity
    EntityID gameStateID = manager.createEntity();
    manager.addComponent<Components::GameStateComponent>(gameStateID, 2);

    EntityID enemyAI = manager.createEntity();
    manager.addComponent<Components::AIComponent>(enemyAI);

    if (Config::ENABLE_DEBUG_SYMBOLS) {
        EntityID debugID = manager.createEntity();
        manager.addComponent<Components::DebugOverlayComponent>(debugID);
    }

    // Generate Map
    Game::GenerateRandomMap(manager, Config::SCREEN_WIDTH*4, Config::SCREEN_HEIGHT*4, 40, 500);

    // Signal Handlers
    // manager.registerSignalHandlers();
}

Scene::~Scene()
{
    log_info << "Destroying Scene";
    log_info << "Releasing GUI resources";
    gui.release();
}

void Scene::update(float dt)
{
    Systems::InputHoverSystem(manager, windowRef);
    Systems::HudSystem(manager, *gui);
    Systems::ProductionSystem(manager, dt);
    Systems::DroneTransferSystem(manager, dt);
    Systems::MovementSystem(manager, dt);
    Systems::ShieldSystem(manager, dt);
    Systems::CombatSystem(manager, dt);
    Systems::LabelUpdateSystem(manager, dt);
    Systems::AI::AISystem(manager, dt);
    Systems::GameStateSystem(manager, dt);
    Systems::DebugOverlaySystem(manager, dt);

    // Handle Camera Movement
    // Needs to be in the update loop
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraPosition.y -= cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPosition.y += cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPosition.x -= cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPosition.x += cameraSpeed * 0.16f;

    // Update Camera
    camera.setCenter(cameraPosition);
    this->windowRef.setView(camera);
}

void Scene::render()
{
    Systems::SpriteUpdateSystem(manager);
    Systems::RenderSystem(manager, windowRef);
    gui->draw();
}

void Scene::handleInput(sf::Event &event)
{
    gui->handleEvent(event);
    Systems::InputSelectionSystem(event, manager, windowRef);

    // Handle Camera Zoom
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta < 0) camera.zoom(1.1f);
        if (event.mouseWheelScroll.delta > 0) camera.zoom(0.9f);
    }
}
