#ifndef WORLDEDITOR_H
#define WORLDEDITOR_H

#include <SFML/Graphics.hpp>

#include "World.h"

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

    private:
        bool checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
        void resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);

        std::string mDirectoryPath;

        sf::Vector2i mLocalMousePosition;
        sf::Vector2f mGlobalMousePosition;
        sf::Vector2f mCameraPosition;

        Camera mCamera;

        std::weak_ptr<WorldObject> mDragObject;
        bool mPlayingHero;
        std::shared_ptr<Player> mHero;

        std::vector<std::shared_ptr<WorldObject>> mWorldObjects;
        std::vector<std::weak_ptr<ICollideable>> mCollideables;

        World mWorld;
};

#endif // WORLDEDITOR_H
