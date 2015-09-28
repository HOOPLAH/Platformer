#include "WorldSwitcher.h"

#include "EntityTags.h"
#include "Projectile.h"

WorldSwitcher::WorldSwitcher(SpriteInfo& info, sf::Vector2f pos, int nextWorld) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::BUTTON),
    mPressed(false),
    mNextWorld(nextWorld)
{
    mPhysicsPosition = pos;
}

WorldSwitcher::~WorldSwitcher()
{
    //dtor
}

void WorldSwitcher::update()
{
    SpriteObject::update();

    mRenderPosition = mPhysicsPosition;
}

bool WorldSwitcher::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::PLAYER || (object.lock()->getTag() == EntityTags::PROJECTILE &&
        static_cast<Projectile*>(&*object.lock())->getOwnerTag() == EntityTags::PLAYER))
        mPressed = true;

    return false;
}
