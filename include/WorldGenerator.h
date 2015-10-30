#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "World.h"

class WorldGenerator
{
    public:
        WorldGenerator();
        ~WorldGenerator();

        std::unique_ptr<World> generateWorld(int diameter, sf::Vector2f pos);

    private:
};

#endif // WORLDGENERATOR_H
