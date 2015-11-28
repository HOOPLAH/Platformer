#include "AIModuleProcessor.h"

#include "NPC.h"
#include "AIAttackModule.h"
#include "AIFollowModule.h"

AIModuleProcessor::AIModuleProcessor(NPC& npc, std::size_t chaserTag) :
    mFollowerTag(chaserTag),
    mNPC(npc)
{
    mCurrentAI = std::make_unique<AIAttackModule>(npc, chaserTag);
}

AIModuleProcessor::~AIModuleProcessor()
{
    //dtor
}

void AIModuleProcessor::update(WorldRef& worldRef)
{
    mCurrentAI->update(worldRef);

    if (length(mNPC.getPhysicsPosition() - mNPC.getTarget().lock()->getPhysicsPosition()) < mNPC.getWeapon().getRange())
        mCurrentAI = std::make_unique<AIAttackModule>(mNPC, mFollowerTag);
    else
        mCurrentAI = std::make_unique<AIFollowModule>(mNPC, mFollowerTag);
}
