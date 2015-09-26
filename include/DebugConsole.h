#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H

#include <map>
#include <vector>
#include <functional>

#include "WorldRef.h"

class DebugConsole
{
    public:
        DebugConsole(WorldRef& worldRef);
        ~DebugConsole();

        std::map<std::string, std::function<void(std::vector<std::string>&)>>& getCommands(){return mCommands;}
        std::vector<std::string>& getLog(){return mLog;}

        int getLogSize(){return mLog.size();}

    private:
        std::map<std::string, std::function<void(std::vector<std::string>&)>> mCommands;
        std::vector<std::string> mLog;

        WorldRef& mWorldRef;
};

#endif // DEBUGCONSOLE_H
