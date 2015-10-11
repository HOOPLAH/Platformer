#include "WorldManager.h"

#include <fstream>
#include <array>

WorldManager::WorldManager(std::weak_ptr<Player> hero)
{
    mCurrentWorld = 0;
    loadWorldFileNames();
    loadWorld(hero);
}

WorldManager::~WorldManager()
{
    //dtor
}

void WorldManager::update(int ticks, std::weak_ptr<Player> hero)
{
    mWorlds[mCurrentWorld]->update(ticks);

    for (auto& button : mWorlds[mCurrentWorld]->getButtons())
        if (button->isPressed())
        {
            mCurrentWorld = button->getNextWorld();
            loadWorld(hero);
            button->setPressed(false);
        }
}

void WorldManager::draw(sf::RenderTarget& target, float alpha)
{
    mWorlds[mCurrentWorld]->draw(target, alpha);
}

void WorldManager::handleEvents(sf::Event event)
{
    mWorlds[mCurrentWorld]->handleEvents(event);
}

void WorldManager::loadWorld(std::weak_ptr<Player> hero)
{
    std::unique_ptr<World> world(new World(hero));
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
