#include "Scene.hpp"

#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"

#include "Utils/Logger.hpp"
#include "Resources/ResourceManager.hpp"
#include "Config.hpp"

#include "Core/Entity.hpp"

#include "Components/FactionComponent.hpp"
#include "Components/Builder.hpp"
#include "Components/FactoryComponent.hpp"
#include "Components/OutpostComponent.hpp"
#include "Components/DroneComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/TagComponent.hpp"
#include "Components/HoverComponent.hpp"

#include "Systems/MovementSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/LabelUpdateSystem.hpp"
#include "Systems/InputSelectionSystem.hpp"
#include "Systems/InputHoverSystem.hpp"
#include "Systems/HudSystem.hpp"
#include "Systems/ProductionSystem.hpp"
#include "Systems/CombatSystem.hpp"
#include "Systems/ShieldSystem.hpp"

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
    Entity background;

    auto& texture = Resource::ResourceManager::getInstance().getTexture(Resource::Paths::BACKGROUND_4);
    background.addComponent(Components::SpriteComponent{texture});
    sf::Vector2u windowSize = sf::Vector2u(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    sf::Vector2u textureSize = texture.getSize();
    background.addComponent(
        Components::TransformComponent{
            sf::Vector2f(0, 0),
            0.f,
            sf::Vector2f(
                static_cast<float>(windowSize.x) / textureSize.x,
                static_cast<float>(windowSize.y) / textureSize.y
            )
        }
    );
    // entities.emplace(background.id, std::move(background));

    // player factory
    float productionRate = 1 + (std::rand() % 1);
    float shieldRegenRate = 1 + (std::rand() % 5);
    auto factory = Builder::createFactory("Factory #" + std::to_string(0), 1, productionRate, shieldRegenRate);
    entities.emplace(factory.id, std::move(factory));

    // Create Neutral Factories
    for(int i=1; i < 10; ++i){
        productionRate = 1 + (std::rand() % 5);
        shieldRegenRate = 1 + (std::rand() % 5);
        auto factory = Builder::createFactory("Factory #" + std::to_string(i), 0, productionRate, shieldRegenRate);
        entities.emplace(factory.id, std::move(factory));
    }

    // Create Outposts
    for(int i=0; i<10; ++i){
        float regenRate = 1 + rand() % 5;
        auto outpost = Builder::createOutpost("Outpost #" + std::to_string(i), 0, regenRate);
        entities.emplace(outpost.id, std::move(outpost));
    }
}

Scene::~Scene()
{
    log_info << "Destroying Scene";
}

void Scene::update(float dt)
{
    Systems::InputHoverSystem(entities, windowRef);
    Systems::HudSystem(entities, *gui);
    Systems::ProductionSystem(entities, dt);
    Systems::MovementSystem(entities, dt);
    Systems::ShieldSystem(entities, dt);
    Systems::CombatSystem(entities, dt);
    Systems::LabelUpdateSystem(entities, dt);

    // Wrap Camera Position
    cameraPosition.x = fmod(cameraPosition.x + Config::MAP_WIDTH, Config::MAP_WIDTH);
    cameraPosition.y = fmod(cameraPosition.y + Config::MAP_HEIGHT, Config::MAP_HEIGHT);
    // Update Camera
    camera.setCenter(cameraPosition);
    this->windowRef.setView(camera);
}

void Scene::render()
{
    Systems::RenderSystem(entities, windowRef);
    gui->draw();
}

void Scene::handleInput(sf::Event &event)
{
    Systems::InputSelectionSystem(event, entities, windowRef);

    log_info << "input";
    // Handle Camera Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraPosition.y -= cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPosition.y += cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPosition.x -= cameraSpeed * 0.16f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPosition.x += cameraSpeed * 0.16f;

}
