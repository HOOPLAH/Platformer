#ifndef IOBJECT_H
#define IOBJECT_H

#include <WorldRef.h>

class IObject
{
    public:
        IObject(){mAlive=true;}
        virtual ~IObject(){}

        virtual void update(WorldRef& worldRef){}

        virtual void respawn(){mAlive=true;}
        virtual void kill(){mAlive=false;}

        bool isAlive(){return mAlive;}

    protected:
        bool mAlive;
};

#endif // IOBJECT_H
