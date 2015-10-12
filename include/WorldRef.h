#ifndef WORLDREF_H
#define WORLDREF_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "WayPointManager.h"

class ICollideable;
class NPC;
class Projectile;
class Player;
class WayPoint;
class WorldObject;
class World;

class WorldRef
{
    public:
        WorldRef(World& world);
        ~WorldRef();

        void addNPC(std::weak_ptr<NPC> npc);
        void addProjectile(std::weak_ptr<Projectile> proj);
        void sq_addProjectile(sf::Vector2f start, float dmg, float range, int ownerTag, float angle);
        void addWorldObject(std::weak_ptr<WorldObject> worldObj);

        std::weak_ptr<Player> getHero();
        std::weak_ptr<WorldObject> getClosestPlatform(sf::Vector2f pos);
        WayPoint getClosestWayPoint(sf::Vector2f pos);
        WayPoint getClosestWayPoint(WayPoint pt);
        WayPointManager& getWayPointManager();
        std::vector<std::weak_ptr<ICollideable>> getObjectsWithinArea(sf::FloatRect rect);

    private:
        World& mWorld;
};

#endif // WORLDREF_H
