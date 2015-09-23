#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include "WorldObject.h"

class TestObject : public WorldObject
{
    public:
        TestObject(SpriteInfo& info, sf::Vector2f pos);
        ~TestObject();

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
        void onContactEnd(std::weak_ptr<ICollideable> object);
};

#endif // TESTOBJECT_H
