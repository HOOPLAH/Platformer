#ifndef WORLDREF_H
#define WORLDREF_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "WayPointManager.h"

class ICollideable;
class SpriteObject;
class Player;
class WayPoint;
class WorldObject;
class World;

class WorldRef
{
    public:
        WorldRef(World& world);
        ~WorldRef();

        void addRenderable(std::weak_ptr<SpriteObject> obj);
        void addCollideable(std::shared_ptr<ICollideable> obj);

        int getTicks();
        std::weak_ptr<Player> getHero();
        std::weak_ptr<ICollideable> getClosestPlatform(sf::Vector2f pos);
        WayPoint getClosestWayPoint(sf::Vector2f pos);
        WayPoint getClosestWayPoint(WayPoint pt);
        WayPointManager& getWayPointManager();
        std::vector<std::weak_ptr<ICollideable>> getObjectsWithinArea(int tag, sf::FloatRect rect);

    private:
        World& mWorld;
};

#endif // WORLDREF_H
