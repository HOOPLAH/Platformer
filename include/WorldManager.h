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
        WorldManager(std::weak_ptr<Player> hero);
        ~WorldManager();

        void update(int ticks, std::weak_ptr<Player> hero);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event event);

    private:
        void loadWorld(std::weak_ptr<Player> hero);
        void loadWorldFileNames();

        int mCurrentWorld;
        std::vector<std::string> mWorldFileNames;
        std::vector<std::unique_ptr<World>> mWorlds;
};

#endif // WORLDMANAGER_H
