#ifndef AIATTACKMODULE_H
#define AIATTACKMODULE_H

#include "IAIModule.h"

class AIAttackModule : public IAIModule
{
    public:
        AIAttackModule(NPC& npc, std::size_t attackerTag);
        ~AIAttackModule();

        void update(WorldRef& worldRef);

    private:
        std::size_t mAttackerTag;
};

#endif // AIATTACKMODULE_H
