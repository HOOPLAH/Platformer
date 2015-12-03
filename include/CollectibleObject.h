#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include "WorldObject.h"

namespace CollectibleType
{
    enum
    {
        AMMOCRATE
    };
}

class CollectibleObject : public WorldObject
{
    public:
        CollectibleObject(SpriteInfo& info, sf::Vector2f pos, int type);
        ~CollectibleObject();

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
        void onContactEnd(std::weak_ptr<ICollideable> object);

        bool isCollected(){return mCollected;}

    private:
        bool mCollected;
        int mType;
};

#endif // TESTOBJECT_H
