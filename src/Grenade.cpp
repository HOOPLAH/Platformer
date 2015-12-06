#include "Grenade.h"

#include "Assets.h"
#include "EntityTags.h"
#include "Constants.h"
#include "NPC.h"

Grenade::Grenade(SpriteInfo& info, sf::Vector2f start, int tag) : Projectile(info, start, 0, 0, tag),
    mExplosion(Assets::sprites["explosion"], mRenderPosition)
{
    mSpeed = 7.f;
    mTag = EntityTags::GRENADE;
    mStatic = false;
    mCollided = false;
    mTime = 2000;

    mSprite.setOrigin(getCenter());

    mExplosion.setFrameLoop(0, 23, false);
    mExplosion.setFrameDelay(12.f);
}

Grenade::~Grenade()
{
    //dtor
}

void Grenade::update(WorldRef& worldRef)
{
    SpriteObject::update();

    mExplosion.setRenderPosition(mExplosionPosition-mExplosion.getCenter());

    if (mTimeUntilExplosion.getElapsedTime().asMilliseconds() >= mTime) // explode
    {
        mExplosionPosition = mRenderPosition;
        mExplosion.setRenderPosition(mExplosionPosition-mExplosion.getCenter());
        for (auto& obj : worldRef.getObjectsWithinArea(EntityTags::NPC,
            sf::FloatRect(mRenderPosition.x-50.f, mRenderPosition.y-50, 100.f, 100.f)))
        {
            static_cast<NPC*>(&*obj.lock())->getHealth().mHP -= 1;
        }

        if (mExplosion.getCurrentFrame() == mExplosion.getEndFrame())
            kill();
    }
    else // wait for explosion
    {
        mOldPhysicsPosition = mPhysicsPosition;
        mPhysicsPosition += mVelocity;
        if (!mCollided)
            mRotation -= 5.f;
        else if (mCollided)
            mRotation -= 0.25f;
    }
}

void Grenade::draw(sf::RenderTarget& target, float alpha)
{
    Projectile::draw(target, alpha);

    if (mTimeUntilExplosion.getElapsedTime().asMilliseconds() >= mTime)
    {
        mExplosion.draw(target, alpha);
    }
}

bool Grenade::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->isStatic() && fromTop)
    {
        mCollided = true;
        mVelocity.x /= 1.5f;
        mVelocity.y = 0.f;
    }
    if (object.lock()->getTag() == EntityTags::PLAYER || object.lock()->getTag() == EntityTags::NPC)
        return false;

    return true;
}
