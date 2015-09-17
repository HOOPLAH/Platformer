#include "WorldObject.h"

#include "EntityTags.h"
#include <Projectile.h>

WorldObject::WorldObject(SpriteInfo& info, sf::Vector2f pos, bool indestructible, int tag, bool _static) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, tag, _static),
    mHealth(100.f, sf::Vector2f(30.f, 2.f))
{
    mPhysicsPosition = pos;
    mIndestructible = true;
    mAlive = true;
    mHealth.mActive = true;
}

WorldObject::~WorldObject()
{
    //dtor
}

void WorldObject::update()
{
    SpriteObject::update();

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, 0.f));
    if (mHealth.mHP <= 0.f && !mIndestructible)
        kill();

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;
    mRenderPosition = mPhysicsPosition;
}

void WorldObject::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    if (!mIndestructible)
        mHealth.draw(target);
}

bool WorldObject::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::PLATFORM)
    {
        return false;
    }
    else if (object.lock()->getTag() == EntityTags::PROJECTILE)
    {
        auto proj = static_cast<Projectile*>(&*object.lock());

        if (proj->getOwnerTag() != mTag)
        {
            if (!mIndestructible)
            {
                mHealth.mHP -= proj->getDamage();
                mHealth.mActive = true;
                mHealth.mActiveClock.restart();
            }
            proj->kill();
        }

        return false;
    }

    return true;
}

void WorldObject::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
