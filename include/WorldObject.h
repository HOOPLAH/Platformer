#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <tuple>

#include "SpriteObject.h"
#include "ICollideable.h"
#include "EntityTags.h"
#include "HealthBar.h"

class WorldObject : public SpriteObject, public ICollideable
{
    public:
        WorldObject(SpriteInfo& info, sf::Vector2f pos, int tag=EntityTags::PLATFORM, bool _static=true, bool hideHealth=true);
        virtual ~WorldObject();

        void update();
        void draw(sf::RenderTarget& target, float alpha);

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
        void onContactEnd(std::weak_ptr<ICollideable> object);

    protected:
        HealthBar mHealth;
};

#endif // WORLDOBJECT_H
