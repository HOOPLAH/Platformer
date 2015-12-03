#ifndef GRENADE_H
#define GRENADE_H

#include "Projectile.h"
#include "WorldRef.h"

class Grenade : public Projectile
{
    public:
        Grenade(SpriteInfo& info, sf::Vector2f start, int tag);
        ~Grenade();

        void update(WorldRef& worldRef);
        void draw(sf::RenderTarget& target, float alpha);
        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);

        void setFiringAngle(float angle){mFiringAngle=angle;}
        float getFiringAngle(){return mFiringAngle;}
        float getSpeed(){return mSpeed;}

    private:
        SpriteObject mExplosion;
        sf::Vector2f mExplosionPosition;
        sf::Clock mTimeUntilExplosion;
        int mTime;
        bool mCollided;
};

#endif // GRENADE_H
