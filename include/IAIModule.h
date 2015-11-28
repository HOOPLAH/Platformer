#ifndef IAIMODULE_H
#define IAIMODULE_H

#include "WorldRef.h"

class NPC;

class IAIModule
{
    public:
        IAIModule(NPC& npc) : mNPC(npc) {}
        virtual ~IAIModule(){}

        virtual void update(WorldRef& worldRef){}

    protected:
        NPC& mNPC; // the npc that this AI is controlling
};

#endif // IAIMODULE_H
