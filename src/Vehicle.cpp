#include "Vehicle.h"

#include "EntityTags.h"

Vehicle::Vehicle(SpriteInfo& info, sf::Vector2f pos) : SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::VEHICLE)

{
    //ctor
}

Vehicle::~Vehicle()
{
    //dtor
}

void Vehicle::update(WorldRef& worldRef)
{
    SpriteObject::update();

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;
}

void Vehicle::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);
}
