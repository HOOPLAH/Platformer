#ifndef AIATTACKMODULE_H
#define AIATTACKMODULE_H

#include "IAIModule.h"

class AIAttackModule : public IAIModule
{
    public:
        AIAttackModule(NPC& npc, bool friendly);
        ~AIAttackModule();

        void update(WorldRef& worldRef);

    private:
        int mAttackerTag;
};

#endif // AIATTACKMODULE_H
