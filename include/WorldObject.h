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

        /*void setJumpPoint(std::tuple<bool, sf::Vector2f> pt){mJumpPoint=pt;}
        std::tuple<bool, sf::Vector2f> getJumpPoint(){return mJumpPoint;}*/

    protected:
        HealthBar mHealth;
        bool mIndestructible;

        //std::tuple<bool, sf::Vector2f> mJumpPoint; // should jump? pos?
};

#endif // WORLDOBJECT_H
