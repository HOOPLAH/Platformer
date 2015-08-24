#include "ContactListener.h"

#include "SpriteObject.h"

ContactListener::ContactListener()
{
    //ctor
}

ContactListener::~ContactListener()
{
    //dtor
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    auto objectA = static_cast<IRenderable*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto objectB = static_cast<IRenderable*>(contact->GetFixtureB()->GetBody()->GetUserData());

    objectA->onPreSolve(objectB, contact, oldManifold);
    objectB->onPreSolve(objectA, contact, oldManifold);
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    auto objectA = static_cast<IRenderable*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto objectB = static_cast<IRenderable*>(contact->GetFixtureB()->GetBody()->GetUserData());

    objectA->onContactBegin(objectB);
    objectB->onContactBegin(objectA);
}

void ContactListener::EndContact(b2Contact* contact)
{
    auto objectA = static_cast<IRenderable*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto objectB = static_cast<IRenderable*>(contact->GetFixtureB()->GetBody()->GetUserData());

    objectA->onContactEnd(objectB);
    objectB->onContactEnd(objectA);
}
