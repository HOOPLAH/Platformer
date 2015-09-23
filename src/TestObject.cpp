#include "TestObject.h"

#include "Player.h"

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
        auto hero = static_cast<Player*>(&*object.lock());

        if (!hero->getQuest().mActions.empty())
        {
            if (hero->getQuest().mActions.top()->mTag == ActionTag::COLLECT)
            {
                auto action = std::static_pointer_cast<CollectAction>(hero->getQuest().mActions.top());

                if (action->mCollectLeftCount > 1)
                    action->mCollectLeftCount--;
                else
                    hero->getQuest().mActions.pop();
            }
        }

        kill();

        return false;
    }

    return true;
}

void TestObject::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
