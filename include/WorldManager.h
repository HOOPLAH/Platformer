#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

// DEFINITION:
//    Manages all worlds. Stores all the worlds and updates the appropriate one

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include "World.h"
#include "WorldGenerator.h"

class WorldManager
{
    public:
        WorldManager();
        ~WorldManager();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event event);

    private:
        WorldGenerator mWorldGenerator;

        std::vector<std::unique_ptr<World>> mWorlds;
};

#endif // WORLDMANAGER_H
