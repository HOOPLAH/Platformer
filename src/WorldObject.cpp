#include "WorldObject.h"

#include "EntityTags.h"
#include <Projectile.h>

WorldObject::WorldObject(SpriteInfo& info, sf::Vector2f pos, int tag, bool _static, bool hideHealth) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, tag, _static),
    mHealth(100.f, sf::Vector2f(30.f, 2.f), hideHealth)
{
    mPhysicsPosition = pos;
    mAlive = true;
    mTag = tag;
}

WorldObject::~WorldObject()
{
    //dtor
}

void WorldObject::update()
{
    SpriteObject::update();

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, 0.f));
    if (mHealth.mHP <= 0.f)
        kill();

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;
}

void WorldObject::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);

    //mHealth.draw(target);
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

        /*if (proj->getOwnerTag() != mTag)
        {
            if (mHealth.mActive)
            {
                mHealth.mHP -= proj->getDamage();
                mHealth.mActiveClock.restart();
            }
        }*/

        proj->kill();

        return false;
    }

    return true;
}

void WorldObject::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
