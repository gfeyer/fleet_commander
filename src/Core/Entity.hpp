#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <typeindex>
#include <memory>

using EntityID = unsigned long;

class Entity {
private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> components;

    // Static variable for unique ID generation
    static EntityID nextID; 

public:
    EntityID id; // Unique Entity ID

    Entity() : id(nextID++) { }

    template<typename T>
    void addComponent(T component) {
        components[std::type_index(typeid(T))] = std::make_shared<T>(component);
    }

    // Get a component
    template<typename T>
    T* getComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        return it != components.end() ? std::static_pointer_cast<T>(it->second).get() : nullptr;
    }

    // Remove a component
    template<typename T>
    void removeComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            components.erase(it);
        }
    }

    // Check if a component exists
    template<typename T>
    bool hasComponent() {
        return components.find(std::type_index(typeid(T))) != components.end();
    }
};


#endif // ENTITY_HPP

