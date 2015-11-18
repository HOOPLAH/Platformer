#ifndef IAIMODULE_H
#define IAIMODULE_H

#include "NPC.h"

class IAIModule
{
    public:
        IAIModule(NPC& npc, bool friendly=true):mNPC(npc){mFriendly=friendly;}
        virtual ~IAIModule(){}

        virtual void update(WorldRef& worldRef){}

        virtual void setFriendly(bool friendly){mFriendly=friendly;}
        bool isFriendly(){return mFriendly;}

    protected:
        NPC& mNPC;
        bool mFriendly; // should i attack player?? applies to most AIs
};

#endif // IAIMODULE_H
