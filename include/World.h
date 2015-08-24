#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "NPC.h"
#include "Camera.h"
#include "WayPointManager.h"
#include "WorldObject.h"
#include "WorldSwitcher.h"
#include "WorldRef.h"

class World
{
    public:
        World(std::string name);
        ~World();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event event);

        void loadWorld(std::string path);

        // Accessor
        std::weak_ptr<Player> getHero(){return mHero;}
        std::vector<std::shared_ptr<NPC>>& getNPCs(){return mNPCs;}
        std::vector<std::shared_ptr<Projectile>>& getProjectiles(){return mAliveProjectiles;}
        std::vector<std::shared_ptr<WorldSwitcher>>& getButtons(){return mButtons;}
        std::vector<std::shared_ptr<WorldObject>>& getWorldObjects(){return mWorldObjects;}
        std::vector<std::weak_ptr<ICollideable>>& getCollideables(){return mCollideables;}
        WayPointManager& getWayPointManager(){return mWayPointManager;}
        WorldRef& getWorldRef(){return mWorldRef;}

    private:
        bool checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
        void resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);

        template <class T>
        std::vector<T> removeDeadObj(std::vector<T>& v);

        template <class T>
        std::vector<T> removeWeakDeadObj(std::vector<T>& v);

        std::string mName;
        WorldRef mWorldRef;

        sf::Vector2f mSpawnPoint;
        std::vector<sf::Vector2f> mNPCSpawnPoints;
        std::size_t mNextNPCSpawnPoint;
        sf::Vector2f mGravity;
        WayPointManager mWayPointManager;

        Camera mCamera;

        std::shared_ptr<Player> mHero; // outlet hero!!
        std::vector<std::shared_ptr<NPC>> mNPCs;
        std::vector<std::shared_ptr<Projectile>> mAliveProjectiles;
        std::vector<std::shared_ptr<WorldSwitcher>> mButtons;
        std::vector<std::shared_ptr<WorldObject>> mWorldObjects;
        std::vector<std::weak_ptr<ICollideable>> mCollideables;
};

#endif // WORLD_H
