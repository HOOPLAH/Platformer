#include "Grenade.h"

#include "EntityTags.h"
#include "Constants.h"

Grenade::Grenade(SpriteInfo& info, sf::Vector2f start, int tag) : Projectile(info, start, 0, 0, tag)
{
    mSpeed = 7.f;
    mTag = EntityTags::GRENADE;
    mStatic = false;
    mCollided = false;
    mTime = 2000;

    mSprite.setOrigin(getCenter());
}

Grenade::~Grenade()
{
    //dtor
}

void Grenade::update()
{
    SpriteObject::update();

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;
    if (!mCollided)
        mRotation -= 5.f;

    if (mTimeUntilExplosion.getElapsedTime().asMilliseconds() >= mTime)
        kill();
}

bool Grenade::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->isStatic() && fromTop)
    {
        mCollided = true;
        mVelocity.x /= 1.5f;
        //mVelocity.y = 0.f;
    }
}
