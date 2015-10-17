#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Line.h"
#include "Projectile.h"
#include "ICollideable.h"
#include "WorldRef.h"

class Weapon : public Item
{
    public:
        Weapon(SpriteInfo& info, int tag);
        ~Weapon();

        virtual void update();
        void draw(sf::RenderTarget& target, float alpha);

        virtual void use(WorldRef& worldRef);
        virtual void fire(WorldRef& ref);

        void addAmmo(int ammo);
        void reload(){if (mMagazines > 0){mAmmo=mMaxAmmo; mMagazines--;}}
        bool checkAmmo();

        // Accessors
        sf::Vector2f getFirePoint(){return mFirePoint;}
        float getRange(){return mRange;}
        int getMaxAmmo(){return mMaxAmmo;}
        int getMaxMagazines(){return mMaxMagazines;}
        int getAmmo(){return mAmmo;}
        int getMagazines(){return mMagazines;}

        // Mutators
        void setDamage(int dmg){mDamage=dmg;}
        void setRange(float range){mRange=range;}
        void setInaccuracy(float inaccuracy){mInaccuracy=inaccuracy;}
        void setCoolDown(int cooldown){mCoolDown=cooldown;}
        void setFiringAngle(float angle){mFiringAngle=angle;}
        void setOwnerTag(int tag){mOwnerTag=tag;}
        void setFirePoint(sf::Vector2f firePoint){mFirePoint=firePoint;}
        void setUnlimitedAmmo(bool unlimited){mUnlimitedAmmo=unlimited;}
        void setWeaponClips(int mag, int ammo){mMagazines=mag; mAmmo=ammo;}

    protected:
        int mDamage;
        float mRange;
        float mInaccuracy;
        int mCoolDown;
        float mFiringAngle;
        int mOwnerTag; // who owns this weapon
        sf::Vector2f mFirePoint;
        sf::Clock mCoolDownClock;

        int mMaxAmmo;
        int mMaxMagazines;
        int mAmmo;
        int mMagazines;
        bool mUnlimitedAmmo;
};

#endif // WEAPON_H
