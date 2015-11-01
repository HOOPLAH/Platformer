#include "WorldGenerator.h"

WorldGenerator::WorldGenerator()
{
    //ctor
}

WorldGenerator::~WorldGenerator()
{
    //dtor
}

std::unique_ptr<World> WorldGenerator::generateWorld(int diameter, sf::Vector2f pos)
{
    auto world = std::make_unique<World>(diameter, pos);
    /*for (std::size_t y = 0; y < diameter; y++)
    {
        for (std::size_t x = 0; x < diameter; x++)
        {
            auto platform = std::make_shared<WorldObject>(Assets::sprites["ammocrate"], pos+
                sf::Vector2f(Assets::sprites["ammocrate"].mFrameDim.x*x, Assets::sprites["ammocrate"].mFrameDim.y*y), EntityTags::PLATFORM);
            world->getWorldRef().addCollideable(platform);
            world->getWorldRef().addRenderable(platform);
        }
    }

    pos = pos+(sf::Vector2f(diameter/2, diameter/2)*Assets::sprites["ammocrate"].mFrameDim.x);
    pos -= sf::Vector2f(Assets::sprites["ammocrate"].mFrameDim.x/2, Assets::sprites["ammocrate"].mFrameDim.x/2);
    world->setPosition(pos);*/

    // x^2 + y^2 = 1
    for (std::size_t i = 0; i < std::max(4, diameter); i++)
    {
        auto x = pos.x + (diameter/2)*cos(i);
        auto y = pos.y + (diameter/2)*sin(i);
        auto platform = std::make_shared<WorldObject>(Assets::sprites["waypoint"], pos+sf::Vector2f(x*8, y*8), EntityTags::PLATFORM);
        world->getWorldRef().addCollideable(platform);
        world->getWorldRef().addRenderable(platform);
    }

    //world->setPosition()

    return world;
}
