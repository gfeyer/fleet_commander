#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <typeindex>
#include "Entity.hpp"

using EntityID = unsigned long;

class EntityManager {
private:
    std::unordered_map<EntityID, Entity> entities; // Main storage
    EntityID nextID = 1; // Unique ID generator

public:

    EntityManager() = default;
    ~EntityManager(){}

    // Prevent copying
    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;

    // Create a new entity and return its unique ID
    EntityID createEntity() {
        EntityID id = nextID++;
        // entities[id] = Entity();
        entities.emplace(id, Entity());
        return id;
    }

    // Remove an entity
    void removeEntity(EntityID id) {
        entities.erase(id);
    }

    // Add a component
    template<typename T>
    void addComponent(EntityID id, T component) {
        entities[id].addComponent<T>(component);
    }

    // Remove a component
    template<typename T>
    void removeComponent(EntityID id) {
        entities[id].removeComponent<T>();
    }

    // Access an entity
    Entity& getEntity(EntityID id) {
        return entities.at(id); // Throws exception if not found
    }

    // Check if an entity exists
    bool hasEntity(EntityID id) const {
        return entities.find(id) != entities.end();
    }

    // Return all entities (if systems need direct access)
    const std::unordered_map<EntityID, Entity>& getAllEntities() const {
        return entities;
    }
};

#endif // ENTITY_MANAGER_HPP
