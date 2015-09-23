#include "TestObject.h"

TestObject::TestObject(SpriteInfo& info, sf::Vector2f pos) : WorldObject(info, pos, EntityTags::COLLECTIBLE, false)
{
    //ctor
}

TestObject::~TestObject()
{
    //dtor
}

bool TestObject::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    WorldObject::onContactBegin(object, fromLeft, fromTop);

    if (object.lock()->getTag() == EntityTags::PLAYER)
    {
        kill();

        return true;
    }

    return true;
}

void TestObject::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
