#include "PhysicsObject.h"

#include "Constants.h"

PhysicsObject::PhysicsObject(SpriteInfo& info, sf::Vector2f pos, b2World& world, b2BodyType type, int tag) :
    SpriteObject(info, pos, tag)
{
    b2BodyDef def;
    def.position.Set(pos.x, pos.y);
    def.type = type;

    mPhysicsBody = world.CreateBody(&def);

    b2PolygonShape boxShape;
    boxShape.SetAsBox((mSpriteInfo.mHitBox.width/pixelsPerMeter)/2, (mSpriteInfo.mHitBox.height/pixelsPerMeter)/2);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;

    mPhysicsBody->CreateFixture(&boxFixtureDef);
    mPhysicsBody->SetUserData(this);
}

PhysicsObject::~PhysicsObject()
{
    //dtor
}

void PhysicsObject::update(float dt)
{
    SpriteObject::update(dt);

    mSprite.setPosition(sf::Vector2f(mPhysicsBody->GetPosition().x*pixelsPerMeter, mPhysicsBody->GetPosition().y*pixelsPerMeter));
    mSprite.setRotation(mPhysicsBody->GetAngle()*DEGTORAD);
}
