#ifndef STARFIELD_H
#define STARFIELD_H

#include <vector>

#include <SFML/Graphics.hpp>
#include "SpriteObject.h"

class Starfield
{
    public:
        Starfield();
        ~Starfield();

        void update();
        void draw(sf::RenderTarget& target, sf::FloatRect windowCoords);

        void addStar(int layer);

    private:
        std::vector<std::vector<SpriteObject>> mLayers;
};

#endif // STARFIELD_H
