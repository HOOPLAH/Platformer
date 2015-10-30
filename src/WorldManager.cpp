#include "WorldManager.h"

#include <fstream>
#include <array>

WorldManager::WorldManager()
{
    mWorlds.push_back(std::move(mWorldGenerator.generateWorld(2, sf::Vector2f())));
}

WorldManager::~WorldManager()
{
    //dtor
}

void WorldManager::update(int ticks)
{
    for (auto& world : mWorlds)
    {
        world->update(ticks);
    }
}

void WorldManager::draw(sf::RenderTarget& target, float alpha)
{
    for (auto& world : mWorlds)
    {
        world->draw(target, alpha);
    }
}

void WorldManager::handleEvents(sf::Event event)
{
    for (auto& world : mWorlds)
    {
        world->handleEvents(event);
    }
}

