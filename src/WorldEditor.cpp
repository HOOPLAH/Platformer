#include "WorldEditor.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Assets.h"
#include "FuncUtils.h"

WorldEditor::WorldEditor(std::string path) :
    mDirectoryPath(path),
    mWorld(path),
    mDebugConsole(mWorld.getWorldRef())
{
    loadWorld();

    mCameraZoom = 1.f;

    mPlayingHero = false;
    mHero = std::make_shared<Player>(Assets::sprites["bluepeewee"], sf::Vector2f(0.f, 0.f));
    mCollideables.push_back(mHero);

    mIDs.push_back("ammocrate");
    mIDs.push_back("blueplatform");
    mIDs.push_back("bigplatform");
    mIDs.push_back("turret");
    mIDs.push_back("waypoint");
    mCurrentID = 0;

    mDebugConsoleActive = false;
    mNextCommandText = sf::Text("", Assets::fonts["8bit"].mFont, 14);
    mNextCommandText.setPosition(0.f, 580.f);
}

WorldEditor::~WorldEditor()
{
    //dtor
}

void WorldEditor::update(int ticks)
{
    if (mPlayingHero)
    {
        mHero->update(mWorld.getWorldRef());
        mCamera.follow(mHero->getRenderPosition());
        mCameraPosition = mHero->getRenderPosition();

        mHero->setVelocity(mHero->getVelocity() + mWorld.getGravity()*UPDATE_STEP.asSeconds());
    }
    else // don't play as hero
    {
        mCameraPosition += mCameraVelocity;
        mCamera.setCenter(mCameraPosition);
    }

    for (auto& obj : mWorldObjects)
    {
        obj->update();
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

    removeWeakDeadObj(mCollideables);
    removeDeadObj(mWorldObjects);
}

void WorldEditor::draw(sf::RenderTarget& target, float alpha)
{
    target.setView(mCamera.getView());
    mGlobalMousePosition = target.mapPixelToCoords(mLocalMousePosition);
    sf::FloatRect windowCoords(mCamera.getCenter().x-(SCREEN_WIDTH/2), mCamera.getCenter().y-(SCREEN_HEIGHT/2), SCREEN_WIDTH, SCREEN_HEIGHT);

    if (mPlayingHero)
        mHero->draw(target, alpha);

    for (auto& obj : mWorldObjects)
    {
        obj->draw(target, alpha);
    }

    auto points = mWorld.getWayPointManager().getWayPoints();
    for (std::size_t i = 0; i < points.size(); i++)
    {
        sf::Text num(std::to_string(i), Assets::fonts["8bit"].mFont, 8);
        num.setPosition(points[i].mPosition+sf::Vector2f(0.f, -10.f));
        target.draw(num);

        for (auto edge : points[i].mEdges)
        {
            sf::Color color = (edge.mType == WayPointType::WALK ? sf::Color::Red : sf::Color::Cyan);
            Line line(points[i].mPosition, points[edge.mTargetIndex].mPosition, color);
            line.draw(target);
        }
    }

    target.setView(target.getDefaultView());

    sf::Text debugText("Debug Console: ", Assets::fonts["8bit"].mFont, 14);
    debugText.setPosition(0.f, 3.f);
    target.draw(debugText);

    std::string idString = "id: ";
    idString.append(mIDs[mCurrentID]);
    sf::Text idText(idString, Assets::fonts["8bit"].mFont, 14);
    idText.setPosition(SCREEN_WIDTH - idText.getGlobalBounds().width, 3.f);
    target.draw(idText);

    std::string zoomString = "zoom: ";
    zoomString.append(std::to_string(mCameraZoom));
    sf::Text zoomText(zoomString, Assets::fonts["8bit"].mFont, 14);
    zoomText.setPosition(SCREEN_WIDTH - zoomText.getGlobalBounds().width, 20.f);
    target.draw(zoomText);

    // hud stuff
    if (!mDebugConsoleActive)
    {
        sf::Text offText("OFF", Assets::fonts["8bit"].mFont, 14);
        offText.setPosition(debugText.getGlobalBounds().width, 3.f);
        offText.setColor(sf::Color::Red);
        target.draw(offText);

        if (!mPlayingHero)
        {
            std::string locMousePosString = "local: ";
            locMousePosString.append(std::to_string(mLocalMousePosition.x));
            locMousePosString.append(", ");
            locMousePosString.append(std::to_string(mLocalMousePosition.y));
            sf::Text locMousePosText(locMousePosString, Assets::fonts["8bit"].mFont, 14);
            locMousePosText.setPosition(0.f, 20.f);
            target.draw(locMousePosText);

            std::string globMousePosString = "global: ";
            globMousePosString.append(std::to_string(sf::Vector2i(mGlobalMousePosition.x, 0.f).x));
            globMousePosString.append(", ");
            globMousePosString.append(std::to_string(sf::Vector2i(0.f, mGlobalMousePosition.y).y));
            sf::Text globMousePosText(globMousePosString, Assets::fonts["8bit"].mFont, 14);
            globMousePosText.setPosition(0.f, 37.f);
            target.draw(globMousePosText);
        }
    }
    else if (mDebugConsoleActive)
    {
        sf::Text onText("ON", Assets::fonts["8bit"].mFont, 14);
        onText.setPosition(debugText.getGlobalBounds().width, 3.f);
        onText.setColor(sf::Color::Green);
        target.draw(onText);

        for (std::size_t i = 0; i < std::min(10, mDebugConsole.getLogSize()); i++) // only show the last 10 commands in debug console
        {
            sf::Text logText(mDebugConsole.getLog()[i], Assets::fonts["8bit"].mFont, 14);
            logText.setPosition(0.f, 20.f + (17.f*i));
            target.draw(logText);
        }

        target.draw(mNextCommandText);
    }
}

void WorldEditor::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2i oldPos = mLocalMousePosition;
        mLocalMousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);

        sf::Vector2i delta = mLocalMousePosition-oldPos;

        if (!mPlayingHero) // not playing as player
        {
            if (!mDragObject.expired())
            {
                mDragObject.lock()->setPhysicsPosition(mDragObject.lock()->getPhysicsPosition()+(sf::Vector2f(delta.x, delta.y)*mCameraZoom));
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Middle)
        {
            mPlayingHero = !mPlayingHero;

            if (mPlayingHero)
                mHero->setPhysicsPosition(mGlobalMousePosition);
        }
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Tab)
        {
            mDebugConsoleActive = !mDebugConsoleActive;
        }
    }
    else if (event.type == sf::Event::TextEntered && mDebugConsoleActive)
    {
        sf::String str = mNextCommandText.getString();

        if (event.text.unicode != 8 && event.text.unicode != 9 && event.text.unicode != 13) // backspace, tab, enter
        {
            str.insert(str.getSize(), static_cast<char>(event.text.unicode));
        }
        else if (event.text.unicode == 8) // backspace
        {
            if (str.getSize() > 1) // for safety
            {
                str.erase(str.getSize()-1);
            }
            else // string is empty
            {
                str = "";
            }
        }
        else if (event.text.unicode == 13) // enter
        {
            auto split_line = splitStringBySpaces(str.toAnsiString());
            if (mDebugConsole.getCommands().count(split_line[0]) > 0) // command exists
            {
                std::string cmd = split_line[0];
                split_line.erase(split_line.begin());
                mDebugConsole.getCommands()[cmd](split_line);
                mDebugConsole.getLog().push_back(str.toAnsiString());
                str = "";
            }
        }

        mNextCommandText.setString(str);
    }
    if (!mPlayingHero) // not playing as hero
    {
        if (event.type == sf::Event::KeyPressed && !mDebugConsoleActive)
        {
            if (mDragObject.expired()) // no object selected
            {
                if (event.key.code == sf::Keyboard::W)
                    mCameraVelocity.y = -5.f;
                else if (event.key.code == sf::Keyboard::S)
                    mCameraVelocity.y = 5.f;

                if (event.key.code == sf::Keyboard::A)
                    mCameraVelocity.x = -5.f;
                else if (event.key.code == sf::Keyboard::D)
                    mCameraVelocity.x = 5.f;
            }
            else
            {
                if (event.key.code == sf::Keyboard::W)
                    mDragObject.lock()->setPhysicsPosition(mDragObject.lock()->getPhysicsPosition()+sf::Vector2f(0.f, -1.f));
                else if (event.key.code == sf::Keyboard::S)
                    mDragObject.lock()->setPhysicsPosition(mDragObject.lock()->getPhysicsPosition()+sf::Vector2f(0.f, 1.f));

                if (event.key.code == sf::Keyboard::A)
                    mDragObject.lock()->setPhysicsPosition(mDragObject.lock()->getPhysicsPosition()+sf::Vector2f(-1.f, 0.f));
                else if (event.key.code == sf::Keyboard::D)
                    mDragObject.lock()->setPhysicsPosition(mDragObject.lock()->getPhysicsPosition()+sf::Vector2f(1.f, 0.f));
            }

            if (event.key.code == sf::Keyboard::Up)
            {
                mCamera.zoom(0.5f);
                mCameraZoom *= 0.5f;
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                mCamera.zoom(2.f);
                mCameraZoom *= 2.f;
            }

            if (event.key.code == sf::Keyboard::Escape)
                saveWorld();
            else if (event.key.code == sf::Keyboard::Delete)
            {
                if (!mDragObject.expired())
                {
                    mDragObject.lock()->kill();
                    mDragObject.reset();
                }
            }
            else if (event.key.code == sf::Keyboard::R) // refresh the world
            {
                saveWorld();
                refreshWorld();
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::W)
                mCameraVelocity.y = 0.f;
            else if (event.key.code == sf::Keyboard::S)
                mCameraVelocity.y = 0.f;

            if (event.key.code == sf::Keyboard::A)
                mCameraVelocity.x = 0.f;
            else if (event.key.code == sf::Keyboard::D)
                mCameraVelocity.x = 0.f;
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::string id = mIDs[mCurrentID];
                float x = mGlobalMousePosition.x;
                float y = mGlobalMousePosition.y;
                auto obj = std::make_shared<WorldEditorObject>(Assets::sprites[id], sf::Vector2f(x, y), id);
                mWorldObjects.push_back(obj);
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                for (auto& obj : mWorldObjects)
                {
                    sf::Vector2f a1 = obj->getPhysicsPosition() + sf::Vector2f(obj->getHitBox().left, obj->getHitBox().top);
                    sf::Vector2f a2 = sf::Vector2f(obj->getHitBox().width, obj->getHitBox().height);
                    sf::FloatRect aRect(a1, a2);

                    if (aRect.contains(mGlobalMousePosition))
                        mDragObject = obj;
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                mDragObject.reset();

                saveWorld();
                refreshWorld();
            }
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            if (event.mouseWheel.delta > 0)
            {
                if (mCurrentID == mIDs.size()-1)
                    mCurrentID = 0;
                else
                    mCurrentID++;
            }

            else if (event.mouseWheel.delta < 0)
            {
                if (mCurrentID == 0)
                    mCurrentID = mIDs.size()-1;
                else
                    mCurrentID--;
            }

        }
    }
    else // playing as player
    {
        if (!mDebugConsoleActive)
            mHero->handleEvents(event, mWorld.getWorldRef());
    }
}

void WorldEditor::loadWorld()
{
    std::string line = "";
    std::ifstream file(mDirectoryPath);

    auto find_key = [](std::string key, std::string line) -> bool
    {
        size_t pos = 0;
        pos = line.find(key);
        if (pos != std::string::npos)
            return true;

        return false;
    };

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            auto split_line = splitStringBySpaces(line);

            if (find_key("platform:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                auto platform = std::make_shared<WorldEditorObject>(Assets::sprites[id], sf::Vector2f(x, y), id);
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
                for (int i = 0; i < amnt; i++)
                {
                    auto platform = std::make_shared<WorldEditorObject>(Assets::sprites[id], sf::Vector2f(start_x+(i*distApart.x),
                                        start_y+(i*distApart.y)), id);
                    mWorldObjects.push_back(platform);
                    mCollideables.push_back(platform);
                }
            }
            else if (find_key("turret:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);

                mWorldObjects.push_back(std::make_shared<WorldEditorObject>(Assets::sprites["turret"], sf::Vector2f(x, y), "turret"));
            }
            else if (find_key("waypoint:", line))
            {
                float x = std::stof(split_line[1]);
                float y = std::stof(split_line[2]);

                mWorldObjects.push_back(std::make_shared<WorldEditorObject>(Assets::sprites["waypoint"], sf::Vector2f(x, y), "waypoint"));
            }
            else if (find_key("waypoint_edge:", line))
            {
                int a = std::stof(split_line[1]);
                int b = std::stof(split_line[2]);
                int type = WayPointType::WALK;
                if (split_line[split_line.size()-2] == "jump")
                    type = WayPointType::JUMP;
                //mWorld.getWayPointManager().addWayPointEdge(a, b, type);
                /*sf::Vector2f start = mWorld.getWayPointManager().getWayPoints()[a].mPosition;
                sf::Vector2f end = mWorld.getWayPointManager().getWayPoints()[b].mPosition;
                auto edge = std::make_shared<WorldEditorObject>(Assets::sprites["pistol"], sf::Vector2f(0, 0), "waypoint_edge");
                mWorldObjects.push_back(edge);*/
            }
        }

        file.close();
    }

    else std::cout << "Unable to open file \'" << mDirectoryPath << "\'\n";
}

void WorldEditor::saveWorld()
{
    std::ofstream file(mDirectoryPath);

    for (auto& obj : mWorldObjects)
    {
        if (obj->getID() == "waypoint")
            file << "waypoint: " << obj->getRenderPosition().x << " " << obj->getRenderPosition().y << "\n";
        else if (obj->getID() == "turret")
            file << "turret: " << obj->getRenderPosition().x << " " << obj->getRenderPosition().y << "\n";
        else
            file << "platform: " << obj->getID() << " " << obj->getRenderPosition().x << " " << obj->getRenderPosition().y << "\n";
    }

    for (auto edge_tuple : mWorld.getWayPointManager().getWayPointEdges())
    {
        WayPointEdge a;
        WayPointEdge b;

        std::tie(a, b) = edge_tuple;

        if (a.mType == WayPointType::WALK)
            file << "waypoint_edge: " << a.mTargetIndex << " " << b.mTargetIndex << "\n";
        else
            file << "waypoint_edge: " << a.mTargetIndex << " " << b.mTargetIndex << " " << "jump" << "\n";
    }

    file.close();
}

void WorldEditor::refreshWorld()
{
    mWorld.resetWorld(mDirectoryPath);
    mWorld.loadWorld(mDirectoryPath);

    mWorldObjects.clear();
    mCollideables.clear();
    mCollideables.push_back(mHero);
    loadWorld();
}

bool WorldEditor::checkCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
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

void WorldEditor::resolveCollision(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
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
void WorldEditor::removeDeadObj(std::vector<T>& v)
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

template <class T>
void WorldEditor::removeWeakDeadObj(std::vector<T>& v)
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
}
