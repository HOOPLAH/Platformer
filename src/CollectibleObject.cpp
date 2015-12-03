#include "CollectibleObject.h"

#include "Player.h"

CollectibleObject::CollectibleObject(SpriteInfo& info, sf::Vector2f pos, int type) : WorldObject(info, pos, EntityTags::COLLECTIBLE, false)
{
    mCollected = false;
    mType = type;
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
        auto player = static_cast<Player*>(&*object.lock());

        if (mType == CollectibleType::AMMOCRATE)
            static_cast<Weapon*>(&*player->getInventory().getItem("Weapon"))->addAmmo(9);

        mCollected = true;

        return true;
    }
    else if (object.lock()->getTag() == EntityTags::NPC)
    {
        return false;
    }

    return true;
}

void CollectibleObject::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
