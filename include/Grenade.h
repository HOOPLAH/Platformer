#ifndef GRENADE_H
#define GRENADE_H

#include "Projectile.h"
#include "WorldRef.h"

class Grenade : public Projectile
{
    public:
        Grenade(SpriteInfo& info, sf::Vector2f start, int tag);
        ~Grenade();

        void update();
        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);

        void setFiringAngle(float angle){mFiringAngle=angle;}
        float getFiringAngle(){return mFiringAngle;}
        float getSpeed(){return mSpeed;}

    private:
        sf::Clock mTimeUntilExplosion;
        int mTime;
        bool mCollided;
};

#endif // GRENADE_H
