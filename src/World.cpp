#include "World.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Assets.h"
#include "Constants.h"
#include "Direction.h"
#include "EntityTags.h"
#include "NPC.h"
#include "WayPoint.h"

World::World(std::string name) :
    mWorldRef(*this),
    mName(name)
{
    mSpawnPoint = sf::Vector2f(0.f, 0.f);
    mNextNPCSpawnPoint = 0;
    mGravity = sf::Vector2f(0.f, 10.f);

    mHero = std::make_shared<Player>(Assets::sprites["bluepeewee"], mSpawnPoint, mWorldRef);
    mCollideables.push_back(mHero);
}

World::~World()
{
    //dtor
}

void World::update(int ticks)
{
    mCollideables = removeWeakDeadObj(mCollideables);
    mNPCs = removeDeadObj(mNPCs);
    mAliveProjectiles = removeDeadObj(mAliveProjectiles);
    mWorldObjects = removeDeadObj(mWorldObjects);
    mButtons = removeDeadObj(mButtons);

    mHero->update();
    mHero->setVelocity(mHero->getVelocity() + mGravity*UPDATE_STEP.asSeconds());
    if (!mHero->isAlive())
    {
        mHero->respawn(mSpawnPoint);
        mCollideables.push_back(mHero);
    }

    if (mNPCs.size() < 6 && mNPCSpawnPoints.size() > 0)
    {
        auto npc = std::make_shared<NPC>(Assets::sprites["pinkpeewee"], mNPCSpawnPoints[mNextNPCSpawnPoint], mWorldRef);
        mNPCs.push_back(npc);
        mCollideables.push_back(npc);

        if (mNextNPCSpawnPoint < mNPCSpawnPoints.size())
            mNextNPCSpawnPoint++;
        else
            mNextNPCSpawnPoint = 0;
    }

    for (auto& npc : mNPCs)
    {
        npc->update(mWorldRef);

        if (ticks%60 == 0) // update AI's paths every second
            npc->setNeedToUpdatePath(true);

        if (!npc->isStatic())
            npc->setVelocity(npc->getVelocity() + mGravity*UPDATE_STEP.asSeconds());
    }

    for (auto& proj : mAliveProjectiles)
    {
        proj->update();
    }

    for (auto& obj : mWorldObjects)
    {
        obj->update();

        if (!obj->isStatic())
            obj->setVelocity(obj->getVelocity() + mGravity*UPDATE_STEP.asSeconds());
    }

    for (auto& button : mButtons)
    {
        button->update();
    }

    // check collisions
    for (std::size_t x = 0; x < mCollideables.size(); x++)
    {
        for (std::size_t y = x+1; y < mCollideables.size(); y++)
        {
            auto dynamic = mCollideables[x];
            auto _static = mCollideables[y];

            if (!mCollideables[x].lock()->isStatic())
                dynamic = mCollideables[x];
            else if (!mCollideables[y].lock()->isStatic())
                dynamic = mCollideables[y];

            if (mCollideables[x].lock()->isStatic())
                _static = mCollideables[x];
            else if (mCollideables[x].lock()->isStatic())
                _static = mCollideables[y];

            if (checkCollision(dynamic, _static))
                resolveCollision(dynamic, _static);
        }
    }

    mCamera.follow(mHero->getRenderPosition());
}

void World::draw(sf::RenderTarget& target, float alpha)
{
    target.setView(mCamera.getView());

    sf::FloatRect windowCoords(mCamera.getCenter().x-(SCREEN_WIDTH/2), mCamera.getCenter().y-(SCREEN_HEIGHT/2), SCREEN_WIDTH, SCREEN_HEIGHT);

    for (auto& npc : mNPCs)
    {
        if (windowCoords.intersects(npc->getSprite().getGlobalBounds()))
            npc->draw(target, alpha);
    }

    for (auto& proj : mAliveProjectiles)
    {
        if (windowCoords.intersects(proj->getSprite().getGlobalBounds()))
            proj->draw(target, alpha);
    }

    for (auto& obj : mWorldObjects)
    {
        if (windowCoords.intersects(obj->getSprite().getGlobalBounds()))
            obj->draw(target, alpha);
    }

    for (auto& button : mButtons)
    {
        if (windowCoords.intersects(button->getSprite().getGlobalBounds()))
            button->draw(target, alpha);
    }

    mHero->draw(target, alpha);

    mWayPointManager.draw(target);

    target.setView(target.getDefaultView());

    mHero->drawStationary(target);
}

void World::handleEvents(sf::Event event)
{
    mHero->handleEvents(event, mWorldRef);
}

void World::loadWorld(std::string path)
{
    std::string line = "";
    std::ifstream file(path);

    auto find_key = [](std::string key, std::string line) -> bool
    {
        size_t pos = 0;
        pos = line.find(key);
        if (pos != std::string::npos)
            return true;

        return false;
    };

    auto split = [](std::string line) -> std::vector<std::string>
    {
        std::istringstream iss(line);
        std::vector<std::string> split_array;
        while (iss)
        {
            std::string sub;
            iss >> sub;
            split_array.push_back(sub);
        }

        return split_array;
    };

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            auto split_line = split(line);

            if (find_key("gravity:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                mGravity = sf::Vector2f(x, y);
            }
            else if (find_key("spawn_point:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                mSpawnPoint = sf::Vector2f(x, y);
                mHero->respawn(mSpawnPoint);
            }
            else if (find_key("npc_spawnpoint:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                mNPCSpawnPoints.push_back(sf::Vector2f(x, y));
            }
            else if (find_key("platform:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                bool indestructible = (split_line[4] == "true");
                auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y), mWorldRef, indestructible, EntityTags::PLATFORM);
                mWorldObjects.push_back(platform);
                mCollideables.push_back(platform);
            }
            else if (find_key("tiled_platforms:", line))
            {
                int amnt = std::stoi(split_line[1]);
                sf::Vector2f distApart(std::stof(split_line[2]), std::stof(split_line[3]));
                std::string id = split_line[4];
                float start_x = std::stof(split_line[5]);
                float start_y = std::stof(split_line[6]);
                bool indestructible = (split_line[7] == "true");
                for (int i = 0; i < amnt; i++)
                {
                    auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(start_x+(i*distApart.x),
                                        start_y+(i*distApart.y)), mWorldRef, indestructible);
                    mWorldObjects.push_back(platform);
                    mCollideables.push_back(platform);
                }
            }
            else if (find_key("button:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                int nextWorld = std::stof(split_line[4]);
                auto button = std::make_shared<WorldSwitcher>(Assets::sprites[id], sf::Vector2f(x, y), nextWorld);
                mButtons.push_back(button);
                mCollideables.push_back(button);
            }
            else if (find_key("waypoint:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                int index = mWayPointManager.getNextWayPointIndex();
                WayPoint pt(x, y, index);
                mWayPointManager.addWayPoint(pt);
            }
            else if (find_key("waypoint_edge:", line))
            {
                int a = std::stof(split_line[1]);
                int b = std::stof(split_line[2]);
                int type = WayPointType::WALK;
                if (split_line[split_line.size()-2] == "jump")
                    type = WayPointType::JUMP;
                mWayPointManager.addWayPointEdge(a, b, type);
            }
        }

        file.close();
    }

    else std::cout << "Unable to open file \'" << path << "\'\n";
}

bool World::checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
    sf::Vector2f a1 = a.lock()->getPhysicsPosition() + sf::Vector2f(a.lock()->getHitBox().left, a.lock()->getHitBox().top);
    sf::Vector2f a2 = sf::Vector2f(a.lock()->getHitBox().width, a.lock()->getHitBox().height);

    sf::Vector2f b1 = b.lock()->getPhysicsPosition() + sf::Vector2f(b.lock()->getHitBox().left, b.lock()->getHitBox().top);
    sf::Vector2f b2 = sf::Vector2f(b.lock()->getHitBox().width, b.lock()->getHitBox().height);

    //float rect = (left, top, width, height)
    sf::FloatRect aRect(a1, a2);
    sf::FloatRect bRect(b1, b2);

    if (aRect.intersects(bRect))
        return true;

    return false;
}

void World::resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
    auto aLeft = a.lock()->getPhysicsPosition().x + a.lock()->getHitBox().left;
    auto aTop = a.lock()->getPhysicsPosition().y + a.lock()->getHitBox().top;
    auto aRight = aLeft + a.lock()->getHitBox().width;
    auto aBottom = aTop + a.lock()->getHitBox().height;

    auto bLeft = b.lock()->getPhysicsPosition().x + b.lock()->getHitBox().left;
    auto bTop = b.lock()->getPhysicsPosition().y + b.lock()->getHitBox().top;
    auto bRight = bLeft + b.lock()->getHitBox().width;
    auto bBottom = bTop + b.lock()->getHitBox().height;

    float overlapLeft {aRight - bLeft};
    float overlapRight {bRight - aLeft};
    float overlapTop {aBottom - bTop};
    float overlapBottom {bBottom - aTop};

    bool fromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool fromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX {fromLeft ? overlapLeft : overlapRight};
    float minOverlapY {fromTop ? overlapTop : overlapBottom};

    auto y_collision = [a, fromTop](float overlapX, float overlapY, bool stair=false)
    {
        if (fromTop)
        {
            if (stair)
            {
                a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
                a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x-5.f, a.lock()->getPhysicsPosition().y - overlapY));
            }
            else
            {
                a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
                a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y - overlapY));
            }
        }
        else if (!fromTop)
        {
            a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
            a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y + overlapY));
        }
    };

    auto x_collision = [a, fromLeft, fromTop, y_collision](float overlapX, float overlapY)
    {
        if (overlapY < 20.f && fromTop) // it's probably a stair
        {
            y_collision(overlapX, overlapY, true);
            return;
        }

        a.lock()->setVelocity(sf::Vector2f(0.f, a.lock()->getVelocity().y));

        if (fromLeft)
        {
            a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x - overlapX, a.lock()->getPhysicsPosition().y));
        }
        else if (!fromLeft)
        {
            a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x + overlapX, a.lock()->getPhysicsPosition().y));
        }
    };

    if (a.lock()->onContactBegin(b, fromLeft, fromTop) && b.lock()->onContactBegin(a, fromLeft, fromTop))
    {
        if (std::abs(minOverlapX) > std::abs(minOverlapY)) // y overlap
        {
            y_collision(minOverlapX, minOverlapY);
        }
        else if (std::abs(minOverlapX) < std::abs(minOverlapY)) // x overlap
        {
            x_collision(minOverlapX, minOverlapY);
        }

        a.lock()->onContactEnd(b);
        b.lock()->onContactEnd(a);
    }
}

template <class T>
std::vector<T> World::removeDeadObj(std::vector<T>& v)
{
    typename std::vector<T>::iterator it;

    for (it = v.begin(); it != v.end();)
    {
        if(!(*it)->isAlive())
        {
            it = v.erase(it);
        }
        else
        {
            it++;
        }
    }

    return v;
}

template <class T>
std::vector<T> World::removeWeakDeadObj(std::vector<T>& v)
{
    typename std::vector<T>::iterator it;

    for (it = v.begin(); it != v.end();)
    {
        if(!(*it).lock()->isAlive())
        {
            it = v.erase(it);
        }
        else
        {
            it++;
        }
    }

    return v;
}
