#ifndef QUEST_H
#define QUEST_H

#include <stack>
#include <memory>

#include "Actions.h"

struct Quest
{
    std::stack<std::shared_ptr<IAction>> mActions;
};

#endif // QUEST_H
