#include "Starfield.h"

#include "Assets.h"
#include "Constants.h"

Starfield::Starfield() :
    mLayers(2)
{
    for (std::size_t i = 0; i < 30; i++)
    {
        addStar(0);
    }

    for (std::size_t i = 0; i < 15; i++)
    {
        addStar(1);
    }
}

Starfield::~Starfield()
{
    //dtor
}

void Starfield::addStar(int layer)
{
    SpriteObject obj(Assets::sprites["star"], sf::Vector2f(rand()%static_cast<int>(SCREEN_WIDTH), rand()%static_cast<int>(SCREEN_HEIGHT)));
    obj.getSprite().setScale(1+layer, 1+layer);
    mLayers[layer].push_back(obj);
}

void Starfield::update()
{
}

void Starfield::draw(sf::RenderTarget& target, sf::FloatRect windowCoords)
{
    for (auto layer : mLayers)
    {
        for (auto rect : layer)
        {
            //if (!windowCoords.intersects(rect.getSprite().getGlobalBounds()))
                rect.setPosition(rect.getRenderPosition() + sf::Vector2f(13.f, 0.f));
            rect.draw(target, 1.f);
        }
    }
}
