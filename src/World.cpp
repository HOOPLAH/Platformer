#include "World.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Assets.h"
#include "Constants.h"
#include "Direction.h"
#include "EntityTags.h"
#include "Grenade.h"
#include "NPC.h"
#include "WayPoint.h"
#include "CollectibleObject.h"
#include "OneWayPlatform.h"
#include "SpaceShip.h"
#include "Turret.h"

World::World() :
    mWorldRef(*this),
    mQuadTree(sf::IntRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT), 0, 3),
    mCollisionResolver(mQuadTree),
    mCommandCenter(Assets::sprites["commandcenter"], sf::Vector2f())
{
    mTicks = 0;

    mSpawnPoint = sf::Vector2f(0.f, 0.f);
    mNextNPCSpawnPoint = 0;
    mNPCSpawnCount = 0;
    mGravity = sf::Vector2f(0.f, 10.f);

    mBackground = sf::Sprite(Assets::sprites["daybackground"].mTexture);
    mHero = std::make_shared<Player>(Assets::sprites["bluepeewee"], mSpawnPoint, mWorldRef);
    //mCollideables.push_back(mHero);

    mTimeOfDay = DAWN;
    mTimeSpeed = 30;
}

World::World(std::string path) : World()
{
    loadWorld(path);
}

World::~World()
{
    //dtor
}

void World::update(int ticks)
{
    mTicks = ticks;
    mQuadTree.setIntRect(mBoundaries);

    removeDeadObjects(mCollideables);
    removeDeadObjects(mRenderables);

    // update time of day
    if (mTicks%mTimeSpeed == 0)
    {
        sf::Color color = mBackground.getColor();

        switch (mTimeOfDay)
        {
            case DAWN:
            {
                int r_ratio = (color.r - 200)/mTimeSpeed;
                int g_ratio = (color.g - 130)/mTimeSpeed;
                int b_ratio = (color.b - 130)/mTimeSpeed;

                color.r -= r_ratio;
                color.g -= g_ratio;
                color.b -= b_ratio;

                mBackground.setColor(color);

                for (auto& obj : mRenderables)
                {
                    obj->getSprite().setColor(color);
                }

                if (std::abs(200-color.r) < mTimeSpeed && std::abs(130-color.g) < mTimeSpeed && std::abs(130-color.b) < mTimeSpeed)
                    mTimeOfDay = DAY;

                break;
            }

            case DAY:
            {
                int r_ratio = (color.r - 255)/mTimeSpeed;
                int g_ratio = (color.g - 255)/mTimeSpeed;
                int b_ratio = (color.b - 255)/mTimeSpeed;

                color.r -= r_ratio;
                color.g -= g_ratio;
                color.b -= b_ratio;

                mBackground.setColor(color);

                for (auto& obj : mRenderables)
                {
                    obj->getSprite().setColor(color);
                }

                if (std::abs(255-color.r) < mTimeSpeed && std::abs(255-color.g) < mTimeSpeed && std::abs(255-color.b) < mTimeSpeed)
                    mTimeOfDay = SUNSET;

                break;
            }

            case SUNSET:
            {
                int r_ratio = (color.r - 244)/mTimeSpeed;
                int g_ratio = (color.g - 129)/mTimeSpeed;
                int b_ratio = (color.b - 116)/mTimeSpeed;

                color.r -= r_ratio;
                color.g -= g_ratio;
                color.b -= b_ratio;

                mBackground.setColor(color);

                for (auto& obj : mRenderables)
                {
                    obj->getSprite().setColor(color);
                }

                if (std::abs(244-color.r) < mTimeSpeed && std::abs(129-color.g) < mTimeSpeed && std::abs(116-color.b) < mTimeSpeed)
                    mTimeOfDay = NIGHT;

                break;
            }

            case NIGHT:
            {
                int r_ratio = (color.r - 80)/mTimeSpeed;
                int g_ratio = (color.g - 80)/mTimeSpeed;
                int b_ratio = (color.b - 130)/mTimeSpeed;

                color.r -= r_ratio;
                color.g -= g_ratio;
                color.b -= b_ratio;

                mBackground.setColor(color);

                for (auto& obj : mRenderables)
                {
                    obj->getSprite().setColor(color);
                }

                if (std::abs(80-color.r) < mTimeSpeed && std::abs(80-color.g) < mTimeSpeed && std::abs(130-color.b) < mTimeSpeed)
                    mTimeOfDay = DAWN;

                break;
            }

            default:
                break;
        }

    }

    /*if (getObjectsWithTag(EntityTags::NPC).size() < mNPCSpawnCount && mNPCSpawnPoints.size() > 0)
    {
        auto npc = std::make_shared<NPC>(Assets::sprites["pinkpeewee"], mNPCSpawnPoints[mNextNPCSpawnPoint], mWorldRef);
        mRenderables.push_back(npc);
        mCollideables.push_back(npc);

        if (mNextNPCSpawnPoint < mNPCSpawnPoints.size() && mNPCSpawnCount > 1)
            mNextNPCSpawnPoint++;
        else if (mNextNPCSpawnPoint >= mNPCSpawnPoints.size() || mNPCSpawnCount == 1)
            mNextNPCSpawnPoint = 0;
    }*/

    mQuadTree.clear();
    for (auto& obj : mCollideables)
    {
        obj->update(mWorldRef);

        if (obj->fallsWithGravity())// && obj->getTag() != EntityTags::VEHICLE)
            obj->setVelocity(obj->getVelocity() + mGravity*UPDATE_STEP.asSeconds());
        if (obj->getPhysicsPosition().y > mBoundaries.top + mBoundaries.height)
            obj->kill();

        mQuadTree.addObject(obj);
    }

    if (!mHero->isAlive())
    {
        mHero->respawn(mSpawnPoint);
        //mCollideables.push_back(mHero);
    }

    for (auto& obj : mRenderables)
    {
        if (obj->isParallaxable())
        {
            obj->setRenderPosition(obj->getRenderPosition() + sf::Vector2f(0.25f, 0.f));
            if (obj->getRenderPosition().x > SCREEN_WIDTH)
                obj->setRenderPosition(sf::Vector2f(-obj->getSpriteInfo().mHitBox.width, obj->getRenderPosition().y));
        }
    }

    mCommandCenter.update();

    mCollisionResolver.update(mCollideables);

    mCamera.follow(mHero->getRenderPosition());
}

void World::draw(sf::RenderTarget& target, float alpha)
{
    target.setView(target.getDefaultView());
    {
        target.draw(mBackground);

        for (auto& obj : mRenderables)
        {
            if (obj->isParallaxable())
            {
                obj->draw(target, alpha);
            }
        }
    }

    target.setView(mCamera.getView());
    {
        mWindowCoords = sf::FloatRect(mCamera.getCenter().x-(SCREEN_WIDTH/2), mCamera.getCenter().y-(SCREEN_HEIGHT/2), SCREEN_WIDTH, SCREEN_HEIGHT);

        mCommandCenter.draw(target, alpha);

        for (auto& obj : mRenderables)
        {
            if (mWindowCoords.intersects(obj->getSprite().getGlobalBounds()) && !obj->isParallaxable() && !obj->isStationary())
                obj->draw(target, alpha);
        }

        mHero->draw(target, alpha);
    }

    target.setView(target.getDefaultView());
    {
        drawStationary(target);
    }
}

void World::drawStationary(sf::RenderTarget& target)
{
    for (auto& obj : mRenderables)
    {
        if (mWindowCoords.intersects(obj->getSprite().getGlobalBounds()) && !obj->isParallaxable() && obj->isStationary())
            obj->draw(target, 1.f);
    }

    mHero->drawStationary(target);
}

void World::handleEvents(sf::Event event)
{
    mHero->handleEvents(event, mWorldRef);
    mCommandCenter.handleEvents(event, mWorldRef);
}

void World::loadWorld(std::string path)
{
    mPathDirectory = path;

    std::string line = "";
    std::ifstream file(path);

    auto find_key = [](std::string key, std::string line) -> bool
    {
        std::size_t pos = 0;
        pos = line.find(key);
        if (pos != std::string::npos)
            return true;

        return false;
    };

    mCollideables.push_back(mHero);

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            auto split_line = splitStringBySpaces(line);

            if (find_key("boundaries:", line))
            {
                float left = std::stof(split_line[1]);
                float top = std::stof(split_line[2]);
                float width = std::stof(split_line[3]);
                float height = std::stof(split_line[4]);
                mBoundaries = sf::IntRect(left, top, width, height);
            }
            else if (find_key("gravity:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                mGravity = sf::Vector2f(x, y);
            }
            else if (find_key("spawnpoint:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                mSpawnPoint = sf::Vector2f(x, y);
                mHero->respawn(mSpawnPoint);
            }
            else if (find_key("npc_spawn_point:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                sf::Vector2f pt(x, y);
                mNPCSpawnPoints.push_back(pt);
            }
            else if (find_key("npc_spawn_count:", line))
            {
                int count = std::stof(split_line[1]);
                mNPCSpawnCount = count;
            }
            else if (find_key("collectible:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                auto obj = std::make_shared<CollectibleObject>(Assets::sprites[id], sf::Vector2f(x, y), CollectibleType::AMMOCRATE);
                if (mBoundaries.contains(x, y))
                {
                    mCollideables.push_back(obj);
                    mRenderables.push_back(obj);
                }
            }
            else if (find_key("platform:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y));
                if (mBoundaries.contains(x, y))
                {
                    mCollideables.push_back(platform);
                    mRenderables.push_back(platform);
                }
            }
            else if (find_key("tiled_platforms:", line))
            {
                int amnt = std::stoi(split_line[1]);
                sf::Vector2f distApart(std::stof(split_line[2]), std::stof(split_line[3]));
                std::string id = split_line[4];
                float start_x = std::stof(split_line[5]);
                float start_y = std::stof(split_line[6]);
                for (int i = 0; i < amnt; i++)
                {
                    auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(start_x+(i*distApart.x),
                                        start_y+(i*distApart.y)));
                    if (mBoundaries.contains(sf::Vector2i(start_x+(i*distApart.x), start_y+(i*distApart.y))))
                    {
                        mCollideables.push_back(platform);
                        mRenderables.push_back(platform);
                    }
                }
            }
            else if (find_key("onewayPlatform:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                auto platform = std::make_shared<OneWayPlatform>(Assets::sprites[id], sf::Vector2f(x, y));
                if (mBoundaries.contains(x, y))
                {
                    mCollideables.push_back(platform);
                    mRenderables.push_back(platform);
                }
            }
            else if (find_key("turret:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                auto turret = std::make_shared<Turret>(Assets::sprites["turretbody"], sf::Vector2f(x, y));
                turret->setPhysicsPosition(sf::Vector2f(x, y));
                if (mBoundaries.contains(x, y))
                {
                    mCollideables.push_back(turret);
                    mRenderables.push_back(turret);
                }
            }
            else if (find_key("spaceship:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                auto ship = std::make_shared<SpaceShip>(Assets::sprites["ship"], sf::Vector2f(x, y));
                ship->setPhysicsPosition(sf::Vector2f(x, y));
                if (mBoundaries.contains(x, y))
                {
                    mCollideables.push_back(ship);
                    mRenderables.push_back(ship);
                }
            }
            else if (find_key("commandcenter:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                mCommandCenter.setRenderPosition(sf::Vector2f(x, y));
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
            else if (find_key("renderonly:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                bool parallax = false;
                bool stationary = false;

                if (split_line[4] == "parallax")
                    parallax = true;
                else if (split_line[4] == "stationary")
                    stationary = true;

                auto obj = std::make_shared<SpriteObject>(Assets::sprites[id], sf::Vector2f(x, y), parallax, stationary);
                mRenderables.push_back(obj);
            }
        }

        file.close();
    }

    else std::cout << "Unable to open file \'" << path << "\'\n";
}

void World::resetWorld(std::string path)
{
    mSpawnPoint = sf::Vector2f(0.f, 0.f);
    mNextNPCSpawnPoint = 0;
    mNPCSpawnCount = 0;
    mGravity = sf::Vector2f(0.f, 10.f);

    mCollideables.clear();
    mRenderables.clear();

    mWayPointManager.getWayPoints().clear();
    mWayPointManager.getWayPointEdges().clear();

    loadWorld(path);
}

template <class T>
void World::removeDeadObjects(std::vector<T>& v)
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
}

std::vector<std::weak_ptr<ICollideable>> World::getObjectsWithTag(int tag)
{
    std::vector<std::weak_ptr<ICollideable>> objs;

    for (auto& obj : mCollideables)
    {
        if (obj->getTag() == tag)
            objs.push_back(obj);
    }

    return objs;
}

bool World::onScreen(std::weak_ptr<ICollideable> obj)
{
    sf::Vector2f a1 = obj.lock()->getPhysicsPosition() + sf::Vector2f(obj.lock()->getHitBox().left, obj.lock()->getHitBox().top);
    sf::Vector2f a2 = sf::Vector2f(obj.lock()->getHitBox().width, obj.lock()->getHitBox().height);
    sf::FloatRect rect(a1, a2);

    if (mWindowCoords.intersects(rect))
        return true;

    return false;
}
