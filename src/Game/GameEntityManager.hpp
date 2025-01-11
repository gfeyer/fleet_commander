#ifndef GAME_ENTITY_MANAGER_HPP
#define GAME_ENTITY_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <entt/entity/registry.hpp>
#include <iostream>

// Include necessary components
#include "Components/FactoryComponent.hpp"
#include "Components/DroneComponent.hpp"
#include "Components/ShieldComponent.hpp"
#include "Components/GameStateComponent.hpp"
#include "Components/AIComponent.hpp"
#include "Components/AttackOrderComponent.hpp"
#include "Game/SignalHandlers.hpp"

#define NullEntityID entt::null
using EntityID = entt::entity;

namespace Game {

    class GameEntityManager {
    private:
        entt::registry registry;

        // Special entities
        EntityID gameStateEntityID{ entt::null };
        EntityID AIEntityID{ entt::null };

    public:
        // Default Constructor
        GameEntityManager() = default;

        // Prevent Copying
        GameEntityManager(const GameEntityManager&) = delete;
        GameEntityManager& operator=(const GameEntityManager&) = delete;

        // Create Entity
        EntityID createEntity() {
            EntityID id = registry.create();
            // std::cout << "Entity created: " << static_cast<std::uint32_t>(id) << "\n";
            return id;
        }

        // Destroy Entity
        void removeEntity(EntityID id) {
            if (registry.valid(id)) {
                registry.destroy(id);
                // std::cout << "Entity destroyed: " << static_cast<std::uint32_t>(id) << "\n";
            }
        }

        // Add Component
        template<typename T, typename... Args>
        T& addComponent(EntityID id, Args&&... args) {
            T& component = registry.emplace<T>(id, std::forward<Args>(args)...);
            // std::cout << "Component added to entity: " << static_cast<std::uint32_t>(id) << "\n";

            if constexpr (std::is_same<T, Components::GameStateComponent>::value) {
                gameStateEntityID = id;
            }
            if constexpr (std::is_same<T, Components::AIComponent>::value) {
                AIEntityID = id;
            }

            return component;
        }

        template<typename T, typename... Args>
        T& addOrReplaceComponent(EntityID id, Args&&... args) {
            T& component = registry.emplace_or_replace<T>(id, std::forward<Args>(args)...);

            if constexpr (std::is_same<T, Components::GameStateComponent>::value) {
                gameStateEntityID = id;
            }
            if constexpr (std::is_same<T, Components::AIComponent>::value) {
                AIEntityID = id;
            }

            return component;
        }


        // Remove Component
        template<typename T>
        void removeComponent(EntityID id) {
            if (registry.all_of<T>(id)) {
                registry.remove<T>(id);
                // std::cout << "Component removed from entity: " << static_cast<std::uint32_t>(id) << "\n";
            }
        }

        // Get Component (Pointer)
        template<typename T>
        T* getComponent(EntityID id) {
            return registry.try_get<T>(id);
        }

        // Check if Entity has a Component
        template<typename T>
        bool hasComponent(EntityID id) {
            return registry.all_of<T>(id);
        }

        template<typename... Components>
        auto view() {
            return registry.view<Components...>();
        }

        // Register on_update Listener
        template<typename T, typename Func>
        void onUpdate(Func&& func) {
            registry.on_update<T>().connect(std::forward<Func>(func));
        }

        // Patch Component
        template<typename T, typename Func>
        void patchComponent(EntityID id, Func&& func) {
            if (registry.all_of<T>(id)) {
                registry.patch<T>(id, std::forward<Func>(func));
                // log_info << "Component patched for entity: " << static_cast<std::uint32_t>(id) << "\n";
            } else {
                log_err << "Cannot patch component: Entity does not have the specified component.\n";
            }
        }

        // Get All Entity IDs
        std::vector<EntityID> getAllEntityIDs() {
            // TODO: temporary until project fully migrated to entt::view 
            std::vector<EntityID> entityIDs;

            // Iterate through the storage of all entities
            auto& storage = registry.storage<entt::entity>();

            for (auto entity : storage) {
                if (registry.valid(entity)) {
                    entityIDs.push_back(entity);
                }
            }

            return entityIDs;
        }

        // Get Game State
        Components::GameStateComponent* getGameStateComponent() {
            if (registry.valid(gameStateEntityID) && registry.all_of<Components::GameStateComponent>(gameStateEntityID)) {
                return &registry.get<Components::GameStateComponent>(gameStateEntityID);
            }
            return nullptr;
        }

        // Get AI
        Components::AIComponent* getAIComponent() {
            if (registry.valid(AIEntityID) && registry.all_of<Components::AIComponent>(AIEntityID)) {
                return &registry.get<Components::AIComponent>(AIEntityID);
            }
            return nullptr;
        }

        void registerSignalHandlers() {
            registry.on_update<Components::AttackOrderComponent>().connect<&SignalHandlers::onAttackOrderUpdate>();
            // Add connections for other components and handlers here
        }
    };
}

#endif // GAME_ENTITY_MANAGER_HPP
