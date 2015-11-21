#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "NPC.h"
#include "Camera.h"
#include "CollisionResolver.h"
#include "Item.h"
#include "Quest.h"
#include "Starfield.h"
#include "QuadTree.h"
#include "WayPointManager.h"
#include "WorldObject.h"
#include "WorldSwitcher.h"
#include "WorldRef.h"

class World
{
    public:
        World();
        World(std::string path);
        ~World();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void drawStationary(sf::RenderTarget& target);
        void handleEvents(sf::Event event);

        void loadWorld(std::string path);
        void resetWorld(std::string path);

        // Accessor
        int getTicks(){return mTicks;}
        sf::Vector2f getGravity(){return mGravity;}
        std::weak_ptr<Player> getHero(){return mHero;}
        std::vector<std::shared_ptr<WorldSwitcher>>& getButtons(){return mButtons;}
        std::vector<std::shared_ptr<SpriteObject>>& getRenderables(){return mRenderables;}
        WayPointManager& getWayPointManager(){return mWayPointManager;}
        CollisionResolver& getCollisionResolver(){return mCollisionResolver;}
        WorldRef& getWorldRef(){return mWorldRef;}

    private:
        bool onScreen(std::weak_ptr<ICollideable> obj);
        std::vector<std::weak_ptr<ICollideable>> getObjectsWithTag(int tag);
        template <class T>
        void removeDeadObjects(std::vector<T>& v);

        std::string mPathDirectory;
        WorldRef mWorldRef;
        int mTicks;

        sf::Vector2f mGravity;
        sf::Vector2f mSpawnPoint;
        std::vector<sf::Vector2f> mNPCSpawnPoints;
        std::size_t mNextNPCSpawnPoint;
        std::size_t mNPCSpawnCount; // how many npcs should be out and about at one time

        WayPointManager mWayPointManager;
        CollisionResolver mCollisionResolver;

        Camera mCamera;
        sf::FloatRect mWindowCoords;
        Starfield mStarField;
        QuadTree mQuadTree;

        std::shared_ptr<Player> mHero; // outlet hero!!
        std::vector<std::shared_ptr<WorldSwitcher>> mButtons;
        std::vector<std::shared_ptr<SpriteObject>> mRenderables;
};

#endif // WORLD_H
