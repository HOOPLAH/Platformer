#ifndef TURRET_H
#define TURRET_H

#include "WorldObject.h"

#include "ICollideable.h"
#include "Weapon.h"
#include "WorldRef.h"

class Turret : public WorldObject
{
    public:
        Turret(SpriteInfo& info, sf::Vector2f pos);
        ~Turret();

        void update(WorldRef& worldRef);
        void draw(sf::RenderTarget& target, float alpha);

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);

    private:
        Weapon mWeapon;
        std::weak_ptr<ICollideable> mWeaponTarget;
        float mWeaponAngle;

        int mOwnerTag;
};

#endif // TURRET_H
