#include "AIAttackModule.h"

#include "NPC.h"

AIAttackModule::AIAttackModule(NPC& npc, std::size_t attackerTag) : IAIModule(npc),
    mAttackerTag(attackerTag)
{
    //ctor
}

AIAttackModule::~AIAttackModule()
{
    //dtor
}

void AIAttackModule::update(WorldRef& worldRef)
{
    if (length(mNPC.getPhysicsPosition() - mNPC.getTarget().lock()->getPhysicsPosition()) < mNPC.getWeapon().getRange())
        mNPC.getWeapon().fire(worldRef);
}
