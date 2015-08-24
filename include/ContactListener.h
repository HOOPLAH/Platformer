#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
    public:
        ContactListener();
        virtual ~ContactListener();

        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        virtual void BeginContact(b2Contact* contact);
        virtual void EndContact(b2Contact* contact);
};

#endif // CONTACTLISTENER_H
