#ifndef ATTACK_ORDER_COMPONENT_HPP
#define ATTACK_ORDER_COMPONENT_HPP


namespace Components {

    struct AttackOrderComponent {
        EntityID origin;
        EntityID target;
        bool isActivated;
        Faction faction = Faction::NEUTRAL; // Who placed this attack order

        AttackOrderComponent() : isActivated(false) {}
        AttackOrderComponent(EntityID origin, EntityID target) : origin(origin), target(target), isActivated(true) {}
    };
}

#endif // ATTACK_ORDER_COMPONENT_HPP