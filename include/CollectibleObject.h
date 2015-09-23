#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include "WorldObject.h"

class CollectibleObject : public WorldObject
{
    public:
        CollectibleObject(SpriteInfo& info, sf::Vector2f pos);
        ~CollectibleObject();

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
        void onContactEnd(std::weak_ptr<ICollideable> object);

        bool isCollected(){return mCollected;}

    private:
        bool mCollected;
};

#endif // TESTOBJECT_H
