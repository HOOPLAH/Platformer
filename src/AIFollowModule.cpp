#include "AIFollowModule.h"

#include "Direction.h"
#include "WorldObject.h"

#include "FuncUtils.h"

AIFollowModule::AIFollowModule(NPC& npc, bool friendly) : IAIModule(npc, friendly)
{
    mFriendly = false;
    mFollowDistance = 15.f;

    mIndex = 0;
}

AIFollowModule::~AIFollowModule()
{
    //dtor
}

void AIFollowModule::update(WorldRef& worldRef)
{
    WayPoint playerWayPt = worldRef.getClosestWayPoint(mNPC.getTarget().getRenderPosition());

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
        if (mNPC.walk(mNPC.getTarget().getRenderPosition()))
        {
            mIndex = 0;
            mWayPoints.clear();
            mNPC.stop();
        }
    }

    if (!mFriendly && length(mNPC.getRenderPosition() - mNPC.getTarget().getRenderPosition()) < mFollowDistance)
        mNPC.getWeapon().fire(mNPC.getWeaponAngle(), worldRef, EntityTags::NPC);
}

/*sf::FloatRect AIFollowModule::getRectBetweenTarget()
{
    sf::FloatRect rect;

    if (npcPos.y - mNPC.getTarget().getRenderPosition().y > -1.f)
    {
        // target is left and above
        if (mNPC.getTarget().getRenderPosition().x < mNPC.getRenderPosition().x)
        {
            rect = sf::FloatRect(mNPC.getTarget().getRenderPosition()+sf::Vector2f(mNPC.getTarget().getHitBox().left, mNPC.getTarget().getHitBox().top),
                                (mNPC.getRenderPosition()+sf::Vector2f(mNPC.getHitBox().width*1.6, mNPC.getHitBox().height*1.1)) -
                                (mNPC.getTarget().getRenderPosition()+sf::Vector2f(mNPC.getTarget().getHitBox().left, mNPC.getTarget().getHitBox().top)));
        }
        // right and above
        if (mNPC.getTarget().getRenderPosition().x > mNPC.getRenderPosition().x)
        {
            rect = sf::FloatRect(mNPC.getRenderPosition()+sf::Vector2f(mNPC.getHitBox().left, mNPC.getHitBox().height),
                                (mNPC.getTarget().getRenderPosition()+sf::Vector2f(mNPC.getTarget().getHitBox().width*1.6, mNPC.getTarget().getHitBox().top*1.1)) -
                                (mNPC.getRenderPosition()+sf::Vector2f(mNPC.getHitBox().left, mNPC.getHitBox().height)));
        }
    }
    else
    {
        // target is left and below
        if (mNPC.getTarget().getRenderPosition().x < mNPC.getRenderPosition().x)
        {
            rect = sf::FloatRect(mNPC.getTarget().getRenderPosition()+sf::Vector2f(mNPC.getTarget().getHitBox().left, mNPC.getTarget().getHitBox().height),
                                (mNPC.getRenderPosition()+sf::Vector2f(mNPC.getHitBox().width*1.6, mNPC.getHitBox().top*1.1)) -
                                (mNPC.getTarget().getRenderPosition()+sf::Vector2f(mNPC.getTarget().getHitBox().left, mNPC.getTarget().getHitBox().height)));
        }
        // right and below
        if (mNPC.getTarget().getRenderPosition().x > mNPC.getRenderPosition().x)
        {
            rect = sf::FloatRect(mNPC.getRenderPosition()+sf::Vector2f(mNPC.getHitBox().left, mNPC.getHitBox().top),
                                (mNPC.getTarget().getRenderPosition()+sf::Vector2f(mNPC.getTarget().getHitBox().width*1.6, mNPC.getTarget().getHitBox().height*1.1)) -
                                (mNPC.getRenderPosition()+sf::Vector2f(mNPC.getHitBox().left, mNPC.getHitBox().top)));
        }
    }

    return rect;
}*/
