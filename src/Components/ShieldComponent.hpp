#ifndef SHIELD_COMPONENT_HPP
#define SHIELD_COMPONENT_HPP

namespace Components {

struct ShieldComponent {
    float currentShield = 0.f;
    float maxShield = 10.f;
    float regenRate = 1.f;
    float regenTimer = 0.f;

    ShieldComponent(){}
    ShieldComponent(float currentShield, float maxShield, float regenRate) : currentShield(currentShield), maxShield(maxShield), regenRate(regenRate) {}

    void setShield(float shield) { currentShield = shield; }
    void incrementShield(float amount = 1.f) { currentShield += amount; }
    void decrementShield(float amount = 1.f) { currentShield -= amount; }
    float getShield() const { return currentShield; }
    };

    // TODO: shield as float for smooth rendering
};

#endif // SHIELD_COMPONENT_HPP