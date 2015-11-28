#ifndef AIMODULEPROCESSOR_H
#define AIMODULEPROCESSOR_H

#include <memory>

#include "IAIModule.h"

class NPC;

class AIModuleProcessor
{
    public:
        AIModuleProcessor(NPC& npc, std::size_t chaserTag); // chaser - follower or attacker
        ~AIModuleProcessor();

        void update(WorldRef& worldRef);

    private:
        std::size_t mFollowerTag;
        std::unique_ptr<IAIModule> mCurrentAI;
        NPC& mNPC;
};

#endif // AIMODULEPROCESSOR_H
