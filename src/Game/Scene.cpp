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
#include "Components/DebugOverlayComponent.hpp"
#include "Components/CursorComponent.hpp"
#include "Components/AnimationComponent.hpp"

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
#include "Systems/AnimationSystem.hpp"

#include "Game/Builder.hpp"
#include "Game/MapGenerator.hpp"

#include "Utils/Random.hpp"

Scene::Scene(sf::RenderWindow& window) : windowRef(window)
{
    log_info << "Creating Scene";

    camera = sf::View(sf::FloatRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT));
    auto cameraPosition = sf::Vector2f(Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2); // Start at center
    camera.setCenter(cameraPosition);

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

    EntityID cursor = manager.createEntity();
    manager.addComponent<Components::CursorComponent>(cursor);
    manager.addComponent<Components::TransformComponent>(cursor, sf::Vector2f(0.f, 0.f), 0.f, sf::Vector2f(1, 1));
    manager.addComponent<Components::SpriteComponent>(cursor);

    if (Config::ENABLE_DEBUG_SYMBOLS) {
        EntityID debugID = manager.createEntity();
        manager.addComponent<Components::DebugOverlayComponent>(debugID);
    }

    // Generate Map
    Game::GenerateRandomMap(manager, Config::SCREEN_WIDTH*4, Config::SCREEN_HEIGHT*4, 40, 500);

    // Signal Handlers
    // manager.registerSignalHandlers();

    // Add a test animation
    EntityID animID = manager.createEntity();
    manager.addComponent<Components::TransformComponent>(animID, sf::Vector2f(0.f, 0.f), 0.f, sf::Vector2f(1, 1));
    manager.addComponent<Components::SpriteComponent>(animID);
    auto* sprite = manager.getComponent<Components::SpriteComponent>(animID);
    sprite->sprite.setTexture(Resource::ResourceManager::getInstance().getTexture(Resource::Paths::TEXTURE_EXPLOSIONS_ATLAS));
    sprite->sprite.setTextureRect(sf::IntRect(0, 0, 1, 1));
    manager.addComponent<Components::AnimationComponent>(animID, "expl_11", 24);
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
    Systems::AnimationSystem(manager, dt);


    // Handle Camera Movement
    // Needs to be in the update loop
    float moveStep = cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.move(0.f, -moveStep);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.move(0.f,  moveStep);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.move(-moveStep, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.move( moveStep, 0.f);

    // Set the updated view
    windowRef.setView(camera);

    // Update Camera
    // camera.setCenter(cameraPosition);
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
    // if (event.type == sf::Event::MouseWheelScrolled) {
    //     // zoom towards where the mouse is pointed
    //     sf::Vector2i mousePos = sf::Mouse::getPosition(windowRef);
        
    //     if (event.mouseWheelScroll.delta < 0) camera.zoom(1.1f);
    //     if (event.mouseWheelScroll.delta > 0) camera.zoom(0.9f);
    // }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            float delta = event.mouseWheelScroll.delta;
            float zoomFactor = (delta > 0) ? 0.9f : 1.1f;
    
            // Step 1: Zoom the camera
            camera.zoom(zoomFactor);
            
            if(delta > 0){
                // Only move on zoom in
                // Get the center of the camera
                sf::Vector2f viewCenter = camera.getCenter();
                sf::Vector2f viewSize = camera.getSize();
        
                // Get mouse position in window (in pixels)
                sf::Vector2i mousePixelPos = sf::Mouse::getPosition(windowRef);
                sf::Vector2f mouseWorldPos = windowRef.mapPixelToCoords(mousePixelPos, camera);
        
                // Compute direction from center to mouse
                sf::Vector2f direction = mouseWorldPos - viewCenter;
        
                // Move a bit (e.g., 10%) toward mouse
                camera.move(direction * 0.15f);
            }
            
            // Apply the new view
            windowRef.setView(camera);
        }
    }
    
    
    
}
