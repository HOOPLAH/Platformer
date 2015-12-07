#ifndef ONEWAYPLATFORM_H
#define ONEWAYPLATFORM_H

#include "WorldObject.h"

class OneWayPlatform : public WorldObject
{
    public:
        OneWayPlatform(SpriteInfo& info, sf::Vector2f pos);
        ~OneWayPlatform();

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
};

#endif // ONEWAYPLATFORM_H
