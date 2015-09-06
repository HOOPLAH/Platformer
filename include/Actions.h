#ifndef IACTION_H
#define IACTION_H

namespace ActionTag
{
    enum
    {
        KILL,
        COLLECT
    };
}

struct IAction
{
    IAction() : mComplete(false), mTag(ActionTag::KILL) {}

    bool mComplete;
    int mTag; // KillAction, CollectAction, etc.
};

struct KillAction : IAction
{
    KillAction() : IAction() {}

    std::size_t mTotalKillCount;
    std::size_t mKillsLeftCount;
    int mKillTag; // EntityTags, who to kill
};

struct CollectAction : IAction
{
    CollectAction() : IAction() {}

    std::size_t mTotalCollectCount;
    std::size_t mCollectLeftCount;
    int mCollectTag; // EntityTags, what to collect
};

#endif // IACTION_H
