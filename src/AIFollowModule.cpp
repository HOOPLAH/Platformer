#include "AIFollowModule.h"

#include "NPC.h"
#include "Direction.h"
#include "WorldObject.h"
#include "FuncUtils.h"

AIFollowModule::AIFollowModule(NPC& npc, std::size_t followerTag) : IAIModule(npc)
{
    mFollowDistance = 15.f;
    mFollowerTag = followerTag;

    mIndex = 0;
}

AIFollowModule::~AIFollowModule()
{
    //dtor
}

void AIFollowModule::update(WorldRef& worldRef)
{
    WayPoint playerWayPt = worldRef.getClosestWayPoint(mNPC.getTarget().lock()->getPhysicsPosition());

    if (mNPC.needToUpdatePath())
    {
        int curWayPtIndex = -1;
        if (!mWayPoints.empty())
        {
            curWayPtIndex = mWayPoints[mIndex]->mIndex;
        }

        worldRef.getWayPointManager().getPath(mWayPoints, worldRef.getClosestWayPoint(mNPC.getFeetPosition()).mIndex, playerWayPt.mIndex);
        mIndex = 0;

        if (curWayPtIndex != -1)
        {
            for (std::size_t i = 0; i < mWayPoints.size(); i++)
            {
                if (mWayPoints[i]->mIndex == std::size_t(curWayPtIndex))
                {
                    mIndex = i;
                }
            }
        }

        mNPC.setNeedToUpdatePath(false);
    }

    if (mIndex+1 < mWayPoints.size())
    {
        if (mNPC.walk(mWayPoints[mIndex]->mPosition)) // npc is now at the point
        {
            auto edge = mWayPoints[mIndex]->getEdge(mWayPoints[mIndex+1]->mIndex);

            if (edge)
            {
                if (edge->mType == WayPointType::JUMP)
                {
                    //if (length(mWayPoints[mIndex]->mPosition-mNPC.getRenderPosition()) > mFollowDistance) // actually needs to jump
                    {
                        int dir = (mNPC.getFeetPosition().x > mWayPoints[mIndex]->mPosition.x) ? Direction::LEFT : Direction::RIGHT;
                        mNPC.jump(dir);
                    }
                }

                mIndex++;
            }
        }
    }
    else
    {
        if (mNPC.walk(mNPC.getTarget().lock()->getPhysicsPosition()) ||
            std::abs(length(mNPC.getTarget().lock()->getPhysicsPosition() - mNPC.getRenderPosition())) > 250.f)
        {
            mIndex = 0;
            mWayPoints.clear();
            mNPC.stop();
        }
    }
}
