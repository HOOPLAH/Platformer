#include "DebugConsole.h"

#include <iostream>

DebugConsole::DebugConsole(WorldRef& worldRef) :
    mWorldRef(worldRef)
{
    mCommands["test"] = [](std::vector<std::string>& param) -> void {std::cout << param[0] << std::endl;};
    mCommands["waypoint_edge"] = [this](std::vector<std::string>& param) -> void
    {
        int start = std::stof(param[0]);
        int end = std::stof(param[1]);
        int type = (param[2] == "walk" || param[2] == "Walk" || param[2] == "WALK" ? WayPointType::WALK : WayPointType::JUMP);
        mWorldRef.getWayPointManager().addWayPointEdge(start, end, type);
    };
}

DebugConsole::~DebugConsole()
{
    //dtor
}
