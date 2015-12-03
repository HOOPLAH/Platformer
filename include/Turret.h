#ifndef TURRET_H
#define TURRET_H

#include "WorldObject.h"

#include "Vehicle.h"
#include "Weapon.h"
#include "WorldRef.h"

class Turret : public Vehicle
{
    public:
        Turret(SpriteInfo& info, sf::Vector2f pos);
        ~Turret();

        void update(WorldRef& worldRef);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event, WorldRef& worldRef);

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);

    private:
        bool mAutoAim;
        Weapon mWeapon;
        sf::Vector2f mMousePosition;
        sf::Vector2f mWeaponTarget;
        float mWeaponAngle;

        HealthBar mHealth;

        int mOwnerTag;
};

#endif // TURRET_H
