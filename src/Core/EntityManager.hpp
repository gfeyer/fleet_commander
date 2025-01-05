#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <unordered_map>
#include <typeindex>
#include "Entity.hpp"

using EntityID_old = unsigned long;

class EntityManager {
private:
    std::unordered_map<EntityID_old, Entity> entities; // Main storage
    EntityID_old nextID = 1; // Unique ID generator

public:

    EntityManager() = default;
    ~EntityManager(){}

    // Prevent copying
    EntityManager(const EntityManager& other) = delete;
    EntityManager& operator=(const EntityManager& other) = delete;

    // Create a new entity and return its unique ID
    EntityID_old createEntity() {
        EntityID_old id = nextID++;
        // entities[id] = Entity();
        entities.emplace(id, Entity());
        return id;
    }

    // Remove an entity
    void removeEntity(EntityID_old id) {
        entities.erase(id);
    }

    // Add a component
    template<typename T>
    void addComponent(EntityID_old id, T component) {
        entities[id].addComponent<T>(component);
    }

    // Remove a component
    template<typename T>
    void removeComponent(EntityID_old id) {
        entities[id].removeComponent<T>();
    }

    // Access an entity
    Entity& getEntity(EntityID_old id) {
        return entities.at(id); // Throws exception if not found
    }

    // Check if an entity exists
    bool hasEntity(EntityID_old id) const {
        return entities.find(id) != entities.end();
    }

    // Return all entities (if systems need direct access)
    const std::unordered_map<EntityID_old, Entity>& getAllEntities() const {
        return entities;
    }

    // Return all entities (if systems need direct access)
    std::unordered_map<EntityID_old, Entity>& getAllEntities() {
        return entities;
    }
};

#endif // ENTITY_MANAGER_HPP
