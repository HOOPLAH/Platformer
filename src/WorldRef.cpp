#include "WorldRef.h"

#include "ICollideable.h"
#include "IRenderable.h"
#include "WayPoint.h"
#include "WorldObject.h"
#include "World.h"

WorldRef::WorldRef(World& world) :
    mWorld(world)
{
    //ctor
}

WorldRef::~WorldRef()
{
    //dtor
}

void WorldRef::addRenderable(std::weak_ptr<SpriteObject> obj)
{
    mWorld.getRenderables().push_back(obj);
}

void WorldRef::addCollideable(std::shared_ptr<ICollideable> obj)
{
    mWorld.getCollideables().push_back(obj);
}

int WorldRef::getTicks()
{
    return mWorld.getTicks();
}

std::weak_ptr<Player> WorldRef::getHero()
{
    return mWorld.getHero();
}

std::weak_ptr<ICollideable> WorldRef::getClosestPlatform(sf::Vector2f pos)
{
    float shortestDist = FLT_MAX;
    std::weak_ptr<ICollideable> closestObj = mWorld.getCollideables()[0];

    for (auto& obj : mWorld.getCollideables())
    {
        if (obj.lock()->getTag() == EntityTags::PLATFORM)
        {
            sf::Vector2f objPos = obj.lock()->getPhysicsPosition();
            float dist = std::abs(sqrt(pow(objPos.x - pos.x , 2) + pow(objPos.y - pos.y, 2)));

            if (dist < shortestDist)
            {
                closestObj = obj;
                shortestDist = dist;
            }
        }
    }

    return closestObj;
}

WayPoint WorldRef::getClosestWayPoint(sf::Vector2f pos)
{
    float shortestDist = FLT_MAX;
    WayPoint closestPt;

    for (auto& pt : mWorld.getWayPointManager().getWayPoints())
    {
        float dist = std::abs(sqrt(pow(pt.mPosition.x - pos.x, 2) + pow(pt.mPosition.y - pos.y, 2)));

        if (dist < shortestDist)
        {
            closestPt = pt;
            shortestDist = dist;
        }
    }

    return closestPt;
}

WayPoint WorldRef::getClosestWayPoint(WayPoint pt)
{
    float shortestDist = FLT_MAX;
    WayPoint closestPt;

    for (auto& new_pt : mWorld.getWayPointManager().getWayPoints())
    {
        float dist = std::abs(sqrt(pow(new_pt.mPosition.x - pt.mPosition.x , 2) + pow(new_pt.mPosition.y - pt.mPosition.y, 2)));

        if (pt.mIndex != new_pt.mIndex)
        {
            if (dist < shortestDist)
            {
                closestPt = new_pt;
                shortestDist = dist;
            }
        }
        else continue;
    }

    return closestPt;
}

WayPointManager& WorldRef::getWayPointManager()
{
    return mWorld.getWayPointManager();
}

std::vector<std::weak_ptr<ICollideable>> WorldRef::getObjectsWithinArea(int tag, sf::FloatRect rect)
{
    std::vector<std::weak_ptr<ICollideable>> nearbyPlatforms;

    for (auto& obj : mWorld.getCollideables())
    {
        if (obj.lock()->getTag() == tag)
        {
            auto pos = obj.lock()->getPhysicsPosition();
            auto hitbox = obj.lock()->getHitBox();

            if (rect.intersects(sf::FloatRect(pos+sf::Vector2f(hitbox.left, hitbox.top), sf::Vector2f(hitbox.width, hitbox.height))))
            {
                nearbyPlatforms.push_back(obj);
            }
        }
    }

    return nearbyPlatforms;
}
