#ifndef SHIELD_COMPONENT_HPP
#define SHIELD_COMPONENT_HPP

namespace Components {

struct ShieldComponent {
    unsigned int currentShield = 0;
    unsigned int maxShield = 10;
    float regenRate = 1.f;
    float regenTimer = 0.f;

    ShieldComponent(){}
    ShieldComponent(unsigned int currentShield, unsigned int maxShield, float regenRate) : currentShield(currentShield), maxShield(maxShield), regenRate(regenRate) {}

    void setShield(unsigned int shield) { currentShield = shield; }
    void incrementShield(unsigned int amount = 1) { currentShield += amount; }
    void decrementShield(unsigned int amount = 1) { currentShield -= amount; }
    unsigned int getShield() const { return currentShield; }
    };

    // TODO: shield as float for smooth rendering
};

#endif // SHIELD_COMPONENT_HPP