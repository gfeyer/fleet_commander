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

Scene::Scene(sf::RenderWindow& window) : windowRef(window)
{
    log_info << "Creating Scene";

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
    auto factory = Builder::createFactory("Factory #" + std::to_string(0), 1);
    entities.emplace(factory.id, std::move(factory));

    // Create Neutral Factories
    for(int i=1; i < 3; ++i){
        auto factory = Builder::createFactory("Factory #" + std::to_string(i));
        entities.emplace(factory.id, std::move(factory));
    }

    // Create Outposts
    for(int i=0; i<3; ++i){
        auto outpost = Builder::createOutpost("Outpost #" + std::to_string(i));
        entities.emplace(outpost.id, std::move(outpost));
    }
}

Scene::~Scene()
{
    log_info << "Destroying Scene";
}

void Scene::update(float dt)
{
    Systems::MovementSystem(entities, dt);
    Systems::InputHoverSystem(entities, windowRef);
    Systems::HudSystem(entities, *gui);
    Systems::ProductionSystem(entities, dt);
    Systems::CombatSystem(entities, dt);
    Systems::LabelUpdateSystem(entities, dt);
}

void Scene::render()
{
    Systems::RenderSystem(entities, windowRef);
    gui->draw();
}

void Scene::handleInput(sf::Event &event)
{
    Systems::InputSelectionSystem(event, entities, windowRef);
}
