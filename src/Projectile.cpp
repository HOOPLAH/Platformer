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
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::update()
{
    SpriteObject::update();

    sf::Vector2f vel = sf::Vector2f(cos(mFiringAngle), sin(mFiringAngle))*(mSpeed*UPDATE_STEP.asSeconds());
    mDistanceLeft -= std::abs(sqrt(pow(vel.x, 2) + pow(vel.y, 2)));
    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += vel;

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
