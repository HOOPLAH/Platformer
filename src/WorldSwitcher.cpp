#include "WorldSwitcher.h"

#include "EntityTags.h"

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
    mPressed = true;

    return false;
}
