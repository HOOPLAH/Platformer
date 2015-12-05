#include "WorldManager.h"

#include <fstream>

WorldManager::WorldManager()
{
    mCurrentWorld = 0;
    loadWorldFileNames();
    loadWorld();
}

WorldManager::~WorldManager()
{
    //dtor
}

void WorldManager::update(int ticks)
{
    mWorlds[mCurrentWorld]->update(ticks);

    /*mCurrentWorld = button->getNextWorld();
    loadWorld();
    button->setPressed(false);*/
}

void WorldManager::draw(sf::RenderTarget& target, float alpha)
{
    mWorlds[mCurrentWorld]->draw(target, alpha);
}

void WorldManager::handleEvents(sf::Event event)
{
    mWorlds[mCurrentWorld]->handleEvents(event);
}

void WorldManager::loadWorld()
{
    std::unique_ptr<World> world(new World);
    world->loadWorld(mWorldFileNames[mCurrentWorld]);
    mWorlds.push_back(std::move(world));
}

void WorldManager::loadWorldFileNames()
{
    std::string line = "";
    std::ifstream file("Content/Worlds/world_filenames.txt");

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            mWorldFileNames.push_back(line);
        }
    }

    file.close();
}
