#include "OneWayPlatform.h"

OneWayPlatform::OneWayPlatform(SpriteInfo& info, sf::Vector2f pos) : WorldObject(info, pos)
{
    //ctor
}

OneWayPlatform::~OneWayPlatform()
{
    //dtor
}

bool OneWayPlatform::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (!fromTop)
        return false;
    else
        return true;
}
