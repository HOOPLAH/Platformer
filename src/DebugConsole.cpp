#include "DebugConsole.h"

#include <iostream>

DebugConsole::DebugConsole()
{
    mCommands["test"] = []() -> void {std::cout << "Hello, World!\n";};
}

DebugConsole::~DebugConsole()
{
    //dtor
}
