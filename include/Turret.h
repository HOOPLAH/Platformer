#ifndef TURRET_H
#define TURRET_H

#include "WorldObject.h"

#include "Weapon.h"
#include "WorldRef.h"

class Turret : public WorldObject
{
    public:
        Turret(SpriteInfo& info, sf::Vector2f pos);
        ~Turret();

        void update(WorldRef& worldRef);
        void draw(sf::RenderTarget& target, float alpha);

    private:
        Weapon mWeapon;
        sf::Vector2f mWeaponTarget;
        float mWeaponAngle;

        int mOwnerTag;
};

#endif // TURRET_H
