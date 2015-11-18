#include "AIAttackModule.h"

AIAttackModule::AIAttackModule(NPC& npc, bool friendly) : IAIModule(npc, friendly)
{
    //ctor
}

AIAttackModule::~AIAttackModule()
{
    //dtor
}

void AIAttackModule::update(WorldRef& worldRef)
{
    if (!mFriendly && length(mNPC.getPhysicsPosition() - mNPC.getTarget().getPhysicsPosition()) < 150)
        mNPC.getWeapon().fire(worldRef);
}
