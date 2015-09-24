#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H

#include <map>
#include <vector>
#include <functional>

class DebugConsole
{
    public:
        DebugConsole();
        ~DebugConsole();

        std::map<std::string, std::function<void()>>& getCommands(){return mCommands;}
        std::vector<std::string>& getLog(){return mLog;}

        int getLogSize(){return mLog.size();}

    private:
        std::map<std::string, std::function<void()>> mCommands;
        std::vector<std::string> mLog;
};

#endif // DEBUGCONSOLE_H
