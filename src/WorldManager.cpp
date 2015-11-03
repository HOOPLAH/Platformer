#include "WorldManager.h"

#include <fstream>
#include <array>

WorldManager::WorldManager()
{
    mWorlds.push_back(std::move(mWorldGenerator.generateWorld(120, sf::Vector2f(0.f, 0.f))));
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

