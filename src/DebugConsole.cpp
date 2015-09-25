#include "DebugConsole.h"

#include <iostream>

DebugConsole::DebugConsole()
{
    mCommands["test"] = [](std::string msg) -> void {std::cout << msg << std::endl;};
}

DebugConsole::~DebugConsole()
{
    //dtor
}
