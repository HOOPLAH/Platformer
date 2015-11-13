#ifndef VEHICLE_H
#define VEHICLE_H

#include "SpriteObject.h"
#include "ICollideable.h"

class Vehicle : public SpriteObject, public ICollideable
{
    public:
        Vehicle(SpriteInfo& info, sf::Vector2f pos);
        virtual ~Vehicle();

        virtual void update(WorldRef& worldRef);
        virtual void draw(sf::RenderTarget& target, float alpha);
        virtual void drawStationary(sf::RenderTarget& target){}
        virtual void handleEvents(sf::Event& event, WorldRef& worldRef){}

    protected:
};

#endif // VEHICLE_H
