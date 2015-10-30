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
    for (std::size_t y = 0; y < diameter; y++)
    {
        for (std::size_t x = 0; x < diameter; x++)
        {
            auto platform = std::make_shared<WorldObject>(Assets::sprites["ammocrate"], pos+
                sf::Vector2f(Assets::sprites["ammocrate"].mFrameDim.x*x, Assets::sprites["ammocrate"].mFrameDim.y*y), EntityTags::PLATFORM);
            world->getWorldRef().addCollideable(platform);
            world->getWorldRef().addRenderable(platform);
        }
    }

    return world;
}
