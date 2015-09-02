#ifndef IACTION_H
#define IACTION_H

namespace ActionTag
{
    enum
    {
        KILL
    };
}

struct IAction
{
    IAction() : mComplete(false), mTag(ActionTag::KILL) {}

    bool mComplete;
    int mTag; // KillAction, etc.
};

struct KillAction : IAction
{
    KillAction() : IAction() {}

    std::size_t mTotalKillCount;
    std::size_t mKillsLeftCount;
    int mKillTag; // EntityTags, who to kill
};

#endif // IACTION_H
