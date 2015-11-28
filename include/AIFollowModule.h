#ifndef AIFOLLOWMODULE_H
#define AIFOLLOWMODULE_H

#include "IAIModule.h"

class AIFollowModule : public IAIModule
{
    public:
        AIFollowModule(NPC& npc, std::size_t followerTag);
        ~AIFollowModule();

        void update(WorldRef& worldRef);

    private:
        float mFollowDistance;
        std::size_t mFollowerTag;

        std::size_t mIndex;
        std::vector<WayPoint*> mWayPoints; // which path npc should take
};

#endif // AIFOLLOWMODULE_H
