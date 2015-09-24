#ifndef WORLDEDITOR_H
#define WORLDEDITOR_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "World.h"
#include "WorldObject.h"
#include "DebugConsole.h"

class WorldEditorObject : public WorldObject
{
    public:
        WorldEditorObject(SpriteInfo& info, sf::Vector2f pos, std::string id) : WorldObject(info, pos), mID(id){}
        ~WorldEditorObject(){}

        std::string getID(){return mID;}

    private:
        std::string mID;
};

class WorldEditor
{
    public:
        WorldEditor(std::string path);
        ~WorldEditor();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

        void loadWorld();
        void saveWorld();
        void refreshWorld();

    private:
        bool checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
        void resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);

        template <class T>
        void removeDeadObj(std::vector<T>& v);
        template <class T>
        void removeWeakDeadObj(std::vector<T>& v);

        std::string mDirectoryPath;

        sf::Vector2i mLocalMousePosition;
        sf::Vector2f mGlobalMousePosition;

        Camera mCamera;
        sf::Vector2f mCameraPosition;
        sf::Vector2f mCameraVelocity;
        float mCameraZoom;

        std::vector<std::string> mIDs;
        int mCurrentID;

        std::weak_ptr<WorldEditorObject> mDragObject;
        bool mPlayingHero;
        std::shared_ptr<Player> mHero;

        bool mDebugConsoleActive;
        DebugConsole mDebugConsole;
        sf::Text mNextCommandText;

        std::vector<std::shared_ptr<WorldEditorObject>> mWorldObjects;
        std::vector<std::weak_ptr<ICollideable>> mCollideables;

        World mWorld;
};

#endif // WORLDEDITOR_H
