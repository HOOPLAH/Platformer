#ifndef AIFOLLOWMODULE_H
#define AIFOLLOWMODULE_H

#include "IAIModule.h"

class AIFollowModule : public IAIModule
{
    public:
        AIFollowModule(NPC& npc, bool friendly=true);
        ~AIFollowModule();

        void update(WorldRef& worldRef);

        void setFriendly(bool friendly){mFriendly=friendly;}

    private:
        //sf::FloatRect getRectBetweenTarget();
        bool mFriendly;
        float mFollowDistance;

        std::size_t mIndex;
        std::vector<WayPoint*> mWayPoints; // which path npc should take
};

#endif // AIFOLLOWMODULE_H
