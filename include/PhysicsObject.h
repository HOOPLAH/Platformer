#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "SpriteObject.h"

#include "Constants.h"

class PhysicsObject : public SpriteObject
{
    public:
        PhysicsObject(SpriteInfo& info, sf::Vector2f pos, b2World& world, b2BodyType type, int tag);
        ~PhysicsObject();

        void update(float dt);

        // Accessor
        sf::Vector2f getPhysicsPosition(){return sf::Vector2f(mPhysicsBody->GetPosition().x, mPhysicsBody->GetPosition().y);}
        b2Body* getPhysicsBody(){return mPhysicsBody;}

        // Mutator
        void setPosition(sf::Vector2f pos)
            {mPhysicsBody->SetTransform(b2Vec2(pos.x/pixelsPerMeter, pos.y/pixelsPerMeter), mPhysicsBody->GetAngle());}

    protected:
        b2Body* mPhysicsBody;
};

#endif // PHYSICSOBJECT_H
