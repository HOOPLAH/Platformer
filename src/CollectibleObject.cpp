#include "CollectibleObject.h"

#include "Player.h"

CollectibleObject::CollectibleObject(SpriteInfo& info, sf::Vector2f pos) : WorldObject(info, pos, EntityTags::COLLECTIBLE, false)
{
    mCollected = false;
}

CollectibleObject::~CollectibleObject()
{
    //dtor
}

bool CollectibleObject::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    WorldObject::onContactBegin(object, fromLeft, fromTop);

    if (object.lock()->getTag() == EntityTags::PLAYER)
    {
        /*auto hero = static_cast<Player*>(&*object.lock());

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
        }*/

        mCollected = true;

        return false;
    }

    return true;
}

void CollectibleObject::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
