#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

// DEFINITION:
//    Manages all worlds. Stores all the worlds and updates the appropriate one

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <squirrel.h>

#include "World.h"

class WorldManager
{
    public:
        WorldManager(HSQUIRRELVM vm);
        ~WorldManager();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event event);

    private:
        void loadWorld();
        void loadWorldFileNames();

        int mCurrentWorld;
        std::vector<std::string> mWorldFileNames;
        std::vector<std::unique_ptr<World>> mWorlds;

        HSQUIRRELVM mVM;
};

#endif // WORLDMANAGER_H
