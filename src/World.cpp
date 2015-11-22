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
#include "Turret.h"

World::World() :
    mWorldRef(*this),
    mQuadTree(sf::IntRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT), 0, 3),
    mCollisionResolver(mQuadTree)
{
    mTicks = 0;

    mSpawnPoint = sf::Vector2f(0.f, 0.f);
    mNextNPCSpawnPoint = 0;
    mNPCSpawnCount = 0;
    mGravity = sf::Vector2f(0.f, 10.f);

    mHero = std::make_shared<Player>(Assets::sprites["bluepeewee"], mSpawnPoint, mWorldRef);
    //mCollisionResolver.getCollideables().push_back(mHero);
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
    mQuadTree.setIntRect(sf::IntRect(mCamera.getCenter().x-(SCREEN_WIDTH/2), mCamera.getCenter().y-(SCREEN_HEIGHT/2), SCREEN_WIDTH, SCREEN_HEIGHT));

    removeDeadObjects(mCollisionResolver.getCollideables());
    removeDeadObjects(mRenderables);
    removeDeadObjects(mButtons);

    //mStarField.update();

    if (getObjectsWithTag(EntityTags::NPC).size() < mNPCSpawnCount && mNPCSpawnPoints.size() > 0)// && !mHero->getQuest().mActions.empty())
    {
        auto npc = std::make_shared<NPC>(Assets::sprites["pinkpeewee"], mNPCSpawnPoints[mNextNPCSpawnPoint], mWorldRef);
        mRenderables.push_back(npc);
        mCollisionResolver.getCollideables().push_back(npc);

        if (mNextNPCSpawnPoint < mNPCSpawnPoints.size())
            mNextNPCSpawnPoint++;
        else
            mNextNPCSpawnPoint = 0;
    }

    //mQuadTree.clear();
    for (auto& obj : mCollisionResolver.getCollideables())
    {
        obj->update(mWorldRef);

        if (!obj->isStatic() && obj->getTag() != EntityTags::VEHICLE && onScreen(obj))
            obj->setVelocity(obj->getVelocity() + mGravity*UPDATE_STEP.asSeconds());
    }

    /*if (!mHero->getQuest().mActions.empty())
    {
        if (!npc->isAlive()) // playah killed npc
        {
            if (mHero->getQuest().mActions.top()->mTag == ActionTag::KILL && npc->getKillerTag() == EntityTags::PLAYER)
            {
                auto action = static_cast<KillAction*>(&*mHero->getQuest().mActions.top());

                if (action->mKillsLeftCount > 1)
                    action->mKillsLeftCount--;
                else
                    mHero->getQuest().mActions.pop();
            }
            else if (mHero->getQuest().mActions.top()->mTag == ActionTag::PROTECT)
            {
                auto action = static_cast<ProtectAction*>(&*mHero->getQuest().mActions.top());

                if (action->mKillsLeftCount > 0)
                    action->mKillsLeftCount--;
            }
        }
    }*/

    /*if (obj->getTag() == EntityTags::COLLECTIBLE)
    {
        auto collectible = static_cast<CollectibleObject*>(&*obj);

        if (collectible->isCollected())
        {
            if (!mHero->getQuest().mActions.empty())
            {
                if (mHero->getQuest().mActions.top()->mTag == ActionTag::COLLECT)
                {
                    auto action = static_cast<CollectAction*>(&*mHero->getQuest().mActions.top());

                    if (obj->getTag() == action->mCollectTag)
                    {
                        if (action->mCollectLeftCount > 1)
                            action->mCollectLeftCount--;
                        else
                            mHero->getQuest().mActions.pop();
                    }
                    else
                        break;
                }
            }

            collectible->kill();
        }
    }*/

    for (auto& button : mButtons)
    {
        if (mHero->getQuest().mActions.empty())
        {
            //button->update();
            button->setCollisionActive(true);
        }
    }

    if (!mHero->isAlive())
    {
        mHero->respawn(mSpawnPoint);
        mCollisionResolver.getCollideables().push_back(mHero);
    }
    mCamera.follow(mHero->getRenderPosition());

    /*for (auto& obj : mCollisionResolver.getCollideables())
    {
        if (!mHero->getQuest().mActions.empty())
        {
            if (mHero->getQuest().mActions.top()->mTag == ActionTag::PROTECT)
            {
                auto action = std::static_pointer_cast<ProtectAction>(mHero->getQuest().mActions.top());
                if (obj.lock()->getTag() == action->mProtectTag)
                {
                    if (obj.lock()->isAlive() && action->mKillsLeftCount == 0) // obj is still alive and player killed everyone
                    {
                        mHero->getQuest().mActions.pop();
                    }
                    else if (!obj.lock()->isAlive())
                    {
                        resetWorld(mPathDirectory);
                    }
                }
            }
        }
    }*/

    mCollisionResolver.update(ticks);
}

void World::draw(sf::RenderTarget& target, float alpha)
{
    target.setView(target.getDefaultView());

    //mStarField.draw(target);

    target.setView(mCamera.getView());

    mWindowCoords = sf::FloatRect(mCamera.getCenter().x-(SCREEN_WIDTH/2), mCamera.getCenter().y-(SCREEN_HEIGHT/2), SCREEN_WIDTH, SCREEN_HEIGHT);

    for (auto& obj : mRenderables)
    {
        if (mWindowCoords.intersects(obj->getSprite().getGlobalBounds()))
            obj->draw(target, alpha);
    }

    for (auto& button : mButtons)
    {
        if (mHero->getQuest().mActions.empty())
        {
            if (mWindowCoords.intersects(button->getSprite().getGlobalBounds()))
                button->draw(target, alpha);
        }
    }

    if (!mHero->inVehicle())
        mHero->draw(target, alpha);
    mWayPointManager.draw(target);

    target.setView(target.getDefaultView());

    drawStationary(target);
}

void World::drawStationary(sf::RenderTarget& target)
{
    mHero->drawStationary(target);
}

void World::handleEvents(sf::Event event)
{
    mHero->handleEvents(event, mWorldRef);
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

    mCollisionResolver.getCollideables().push_back(mHero);

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            auto split_line = splitStringBySpaces(line);

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
                mCollisionResolver.getCollideables().push_back(obj);
                mRenderables.push_back(obj);
            }
            else if (find_key("platform:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y), EntityTags::PLATFORM);
                mCollisionResolver.getCollideables().push_back(platform);
                mRenderables.push_back(platform);
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
                    mCollisionResolver.getCollideables().push_back(platform);
                    mRenderables.push_back(platform);
                }
            }
            else if (find_key("turret:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);
                auto turret = std::make_shared<Turret>(Assets::sprites["turretbody"], sf::Vector2f(x, y));
                mCollisionResolver.getCollideables().push_back(turret);
                mRenderables.push_back(turret);
            }
            else if (find_key("button:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                int nextWorld = std::stof(split_line[4]);
                auto button = std::make_shared<WorldSwitcher>(Assets::sprites[id], sf::Vector2f(x, y), nextWorld);
                button->setCollisionActive(false); // turn off collisions by default until all quests are complete
                mButtons.push_back(button);
                mCollisionResolver.getCollideables().push_back(button);
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
            else if (find_key("quest_action:", line))
            {
                std::string action_type = split_line[1];

                if (action_type == "kill")
                {
                    auto action = std::make_shared<KillAction>();
                    action->mTotalKillCount = std::stof(split_line[2]);
                    action->mKillsLeftCount = action->mTotalKillCount;
                    action->mKillTag = std::stof(split_line[3]);

                    mHero->getQuest().mActions.push(action);
                }
                else if (action_type == "collect")
                {
                    auto action = std::make_shared<CollectAction>();
                    action->mTotalCollectCount = std::stof(split_line[2]);
                    action->mCollectLeftCount = action->mTotalCollectCount;
                    action->mCollectTag = std::stof(split_line[3]);

                    mHero->getQuest().mActions.push(action);
                }
                else if (action_type == "protect")
                {
                    auto action = std::make_shared<ProtectAction>();
                    // kill quest
                    action->mTotalKillCount = std::stof(split_line[2]);
                    action->mKillsLeftCount = action->mTotalKillCount;
                    action->mKillTag = std::stof(split_line[3]);
                    // protect quest
                    action->mProtectTag = std::stof(split_line[4]);
                    action->mTag = ActionTag::PROTECT;

                    mHero->getQuest().mActions.push(action);
                }
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

    mCollisionResolver.getCollideables().clear();
    mRenderables.clear();

    mWayPointManager.getWayPoints().clear();

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

    for (auto& obj : mCollisionResolver.getCollideables())
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
