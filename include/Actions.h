#ifndef IACTION_H
#define IACTION_H

namespace ActionTag
{
    enum
    {
        KILL,
        COLLECT,
        PROTECT
    };
}

struct IAction
{
    IAction() : mComplete(false), mTag(ActionTag::PROTECT) {}

    bool mComplete;
    int mTag; // KillAction, CollectAction, ProtectAction, etc.
};

struct KillAction : IAction
{
    KillAction() : IAction() {mTag=ActionTag::KILL;}

    std::size_t mTotalKillCount;
    std::size_t mKillsLeftCount;
    int mKillTag; // EntityTags, whom to kill
};

struct CollectAction : IAction
{
    CollectAction() : IAction() {mTag=ActionTag::COLLECT;}

    std::size_t mTotalCollectCount;
    std::size_t mCollectLeftCount;
    int mCollectTag; // EntityTags, what to collect
};

struct ProtectAction : IAction
{
    ProtectAction() : IAction() {mTag=ActionTag::PROTECT;}

    std::size_t mTotalKillCount;
    std::size_t mKillsLeftCount;
    int mKillTag; // EntityTags, whom to kill
    int mProtectTag; // EntityTags, whom to protect
};

#endif // IACTION_H
