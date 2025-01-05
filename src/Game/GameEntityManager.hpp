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
            std::cout << "Entity created: " << static_cast<std::uint32_t>(id) << "\n";
            return id;
        }

        // Destroy Entity
        void removeEntity(EntityID id) {
            if (registry.valid(id)) {
                registry.destroy(id);
                std::cout << "Entity destroyed: " << static_cast<std::uint32_t>(id) << "\n";
            }
        }

        // Add Component
        template<typename T, typename... Args>
        T& addComponent(EntityID id, Args&&... args) {
            T& component = registry.emplace<T>(id, std::forward<Args>(args)...);
            std::cout << "Component added to entity: " << static_cast<std::uint32_t>(id) << "\n";

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
                std::cout << "Component removed from entity: " << static_cast<std::uint32_t>(id) << "\n";
            }
        }

        // Get Component (Pointer)
        template<typename T>
        T* getComponent(EntityID id) {
            if (registry.valid(id) && registry.all_of<T>(id)) {
                return &registry.get<T>(id);
            }
            return nullptr;
        }

        // Check if Entity has a Component
        template<typename T>
        bool hasComponent(EntityID id) {
            return registry.all_of<T>(id);
        }

        template<typename... Components>
        auto getView() {
            return registry.view<Components...>();
        }


        // Get All Entity IDs
        std::vector<EntityID> getAllEntityIDs() const {
            std::vector<EntityID> entityIDs;

             // TODO
            
            // Iterate through all valid entities
            // for (auto entity : registry.storage<entt::entity>()) {
            //     if (registry.valid(entity)) {
            //         entityIDs.push_back(entity);
            //     }
            // }

            return entityIDs;
        }


        // Get Game State Entity
        EntityID getGameStateEntityID() const {
            return gameStateEntityID;
        }

        template<typename T>
        T* getGameStateComponent() {
            return getComponent<T>(gameStateEntityID);
        }

        // Get AI Entity
        EntityID getAIEntityID() const {
            return AIEntityID;
        }

        template<typename T>
        T* getAIComponent() {
            return getComponent<T>(AIEntityID);
        }

        // Get Registry (For Advanced Use)
        entt::registry& getRegistry() {
            return registry;
        }
    };
}

#endif // GAME_ENTITY_MANAGER_HPP
