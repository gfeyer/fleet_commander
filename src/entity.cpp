#include "entity.hpp"

unsigned long Entity::nextID = 1; // Start IDs from 1

Entity::Entity() : id(nextID++) 
{
}

template <typename T>
inline void Entity::addComponent(T component)
{
    components[std::type_index(typeid(T))] = std::make_shared<T>(component);
}

template<typename T>
T* Entity::getComponent() {
    auto it = components.find(std::type_index(typeid(T)));
    return it != components.end() ? std::static_pointer_cast<T>(it->second).get() : nullptr;
}

template<typename T>
void removeComponent() {
    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()) {
        components.erase(it);
    }
}

template<typename T>
bool hasComponent() {
    return components.find(std::type_index(typeid(T))) != components.end();
}

