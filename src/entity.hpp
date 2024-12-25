#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <typeindex>
#include <memory>

class Entity {
private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> components;

    // Static variable for unique ID generation
    static unsigned long nextID; 

public:
    unsigned long id; // Unique Entity ID

    Entity();

    template<typename T>
    void addComponent(T component);

    // Get a component
    template<typename T>
    T* getComponent();

    // Remove a component
    template<typename T>
    void removeComponent();

    // Check if a component exists
    template<typename T>
    bool hasComponent();
};

#endif // ENTITY_HPP

