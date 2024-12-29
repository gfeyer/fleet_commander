#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <typeindex>
#include <memory>

// Forward declaration to avoid circular dependency
class EntityManager;

class Entity {
private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> components;

protected:
    // These functions are protected so they can only be called by the manager class which holds the lists
    template<typename T>
    void addComponent(T component) {
        components[std::type_index(typeid(T))] = std::make_shared<T>(component);
    }
    template<typename T>
    void removeComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            components.erase(it);
        }
    }
    friend class EntityManager;
public:

    Entity() = default;
    ~Entity() {}

    // Move constructor
    Entity(Entity&& other) noexcept = default;

    // Prevent copying
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& other) = delete;

    // Get a component
    template<typename T>
    T* getComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        return it != components.end() ? std::static_pointer_cast<T>(it->second).get() : nullptr;
    }

    template<typename T>
    const T* getComponent() const{
        auto it = components.find(std::type_index(typeid(T)));
        return it != components.end() ? std::static_pointer_cast<T>(it->second).get() : nullptr;
    }

    // Check if a component exists
    template<typename T>
    bool hasComponent() {
        return components.find(std::type_index(typeid(T))) != components.end();
    }

    template<typename T>
    const bool hasComponent() const{
        return components.find(std::type_index(typeid(T))) != components.end();
    }
};


#endif // ENTITY_HPP

