#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <tuple>

#include "SpriteObject.h"
#include "ICollideable.h"
#include "WorldRef.h"
#include "EntityTags.h"
#include "HealthBar.h"

class WorldObject : public SpriteObject, public ICollideable
{
    public:
        WorldObject(SpriteInfo& info, sf::Vector2f pos, WorldRef& worldRef, bool indestructible=false, int tag=EntityTags::PLATFORM, bool _static=true);
        virtual ~WorldObject();

        void update();
        void draw(sf::RenderTarget& target, float alpha);

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
        void onContactEnd(std::weak_ptr<ICollideable> object);

    protected:
        HealthBar mHealth;
        bool mIndestructible;
};

#endif // WORLDOBJECT_H
