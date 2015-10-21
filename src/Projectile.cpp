#include "Projectile.h"

#include "EntityTags.h"

#include <iostream>

Projectile::Projectile(SpriteInfo& info, sf::Vector2f pos, int damage, float range, int ownerTag) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::PROJECTILE, false)
    //mLine(start, end, sf::Color(0.f, 191.f, 255.f, 255.f))
{
    mDamage = damage;
    mSpeed = 1000.f;
    mFiringAngle = 0.f;
    mDistanceLeft = range;
    mAlive = true;
    mOwnerTag = ownerTag;
    mPhysicsPosition = pos;
    mRenderPosition = pos;
    mSprite.setPosition(pos);
    mTag = EntityTags::PROJECTILE;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::update(WorldRef& worldRef)
{
    SpriteObject::update();

    mRotation = mFiringAngle*RADTODEG;
    mVelocity = sf::Vector2f(cos(mFiringAngle), sin(mFiringAngle))*(mSpeed*UPDATE_STEP.asSeconds());
    mDistanceLeft -= std::abs(sqrt(pow(mVelocity.x, 2) + pow(mVelocity.y, 2)));
    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;

    if (mDistanceLeft <= 0.f)
    {
        kill();
    }
}

void Projectile::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);
}
