#include "Grenade.h"

#include "EntityTags.h"

Grenade::Grenade(SpriteInfo& info, sf::Vector2f pos) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::GRENADE)
{
    //ctor
}

Grenade::~Grenade()
{
    //dtor
}
