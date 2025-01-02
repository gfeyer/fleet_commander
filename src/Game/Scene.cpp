#include "Scene.hpp"

#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"

#include "Utils/Logger.hpp"
#include "Resources/ResourceManager.hpp"
#include "Config.hpp"

#include "Core/Entity.hpp"

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
    EntityID gameStateID = entityManager.createEntity();
    entityManager.addComponent(gameStateID, Components::GameStateComponent{2});

    EntityID enemyAI = entityManager.createEntity();
    entityManager.addComponent(enemyAI, Components::AIComponent{});

    // Generate Map
    Game::GenerateRandomMap(entityManager, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 30, 100);
}

Scene::~Scene()
{
    log_info << "Destroying Scene";
    log_info << "Releasing GUI resources";
    gui.release();
}

void Scene::update(float dt)
{
    Systems::InputHoverSystem(entityManager, windowRef);
    Systems::HudSystem(entityManager, *gui);
    Systems::ProductionSystem(entityManager, dt);
    Systems::DroneTransferSystem(entityManager, dt);
    Systems::MovementSystem(entityManager, dt);
    Systems::ShieldSystem(entityManager, dt);
    Systems::CombatSystem(entityManager, dt);
    Systems::LabelUpdateSystem(entityManager, dt);
    Systems::AI::AISystem(entityManager, dt);
    Systems::GameStateSystem(entityManager, dt);

    // Wrap Camera Position
    cameraPosition.x = fmod(cameraPosition.x + Config::MAP_WIDTH, Config::MAP_WIDTH);
    cameraPosition.y = fmod(cameraPosition.y + Config::MAP_HEIGHT, Config::MAP_HEIGHT);
    // Update Camera
    camera.setCenter(cameraPosition);
    this->windowRef.setView(camera);
}

void Scene::render()
{
    Systems::RenderSystem(entityManager, windowRef);
    gui->draw();
}

void Scene::handleInput(sf::Event &event)
{
    gui->handleEvent(event);
    Systems::InputSelectionSystem(event, entityManager, windowRef);

    // Handle Camera Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraPosition.y -= cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPosition.y += cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPosition.x -= cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPosition.x += cameraSpeed * 0.16f;

}
