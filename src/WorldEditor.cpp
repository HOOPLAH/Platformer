#include "WorldEditor.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Assets.h"

WorldEditor::WorldEditor(std::string path) :
    mDirectoryPath(path)
{
    loadWorld();
}

WorldEditor::~WorldEditor()
{
    //dtor
}

void WorldEditor::update(int ticks)
{
    mCamera.setCenter(mCameraPosition);

    for (auto& obj : mWorldObjects)
    {
        obj->update();
    }
}

void WorldEditor::draw(sf::RenderTarget& target, float alpha)
{
    target.setView(mCamera.getView());

    mGlobalMousePosition = target.mapPixelToCoords(mLocalMousePosition);

    sf::FloatRect windowCoords(mCamera.getCenter().x-(SCREEN_WIDTH/2), mCamera.getCenter().y-(SCREEN_HEIGHT/2), SCREEN_WIDTH, SCREEN_HEIGHT);

    for (auto& obj : mWorldObjects)
    {
        if (windowCoords.intersects(obj->getSprite().getGlobalBounds()))
            obj->draw(target, alpha);
    }

    target.setView(target.getDefaultView());

    // hud stuff
    std::string locMousePosString = "local: ";
    locMousePosString.append(std::to_string(mLocalMousePosition.x));
    locMousePosString.append(", ");
    locMousePosString.append(std::to_string(mLocalMousePosition.y));
    sf::Text locMousePosText(locMousePosString, Assets::fonts["8bit"].mFont, 14);
    locMousePosText.setPosition(0.f, 3.f);
    target.draw(locMousePosText);

    std::string globMousePosString = "global: ";
    globMousePosString.append(std::to_string(sf::Vector2i(mGlobalMousePosition.x, 0.f).x));
    globMousePosString.append(", ");
    globMousePosString.append(std::to_string(sf::Vector2i(0.f, mGlobalMousePosition.y).y));
    sf::Text globMousePosText(globMousePosString, Assets::fonts["8bit"].mFont, 14);
    globMousePosText.setPosition(0.f, 20.f);
    target.draw(globMousePosText);
}

void WorldEditor::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        mLocalMousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            mCameraPosition.y -= 5;
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            mCameraPosition.y += 5;
        }

        if (event.key.code == sf::Keyboard::A)
        {
            mCameraPosition.x -= 5;
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            mCameraPosition.x += 5;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            saveWorld();
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        std::string id = "ammocrate";
        float x = mGlobalMousePosition.x;
        float y = mGlobalMousePosition.y;
        auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y), true, EntityTags::PLATFORM);
        mWorldObjects.push_back(platform);
        mCollideables.push_back(platform);
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

            if (find_key("platform:", line))
            {
                std::string id = split_line[1];
                float x = std::stof(split_line[2]);
                float y = std::stof(split_line[3]);
                bool indestructible = (split_line[4] == "true");
                auto platform = std::make_shared<WorldObject>(Assets::sprites[id], sf::Vector2f(x, y), indestructible, EntityTags::PLATFORM);
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
                                        start_y+(i*distApart.y)), indestructible);
                    mWorldObjects.push_back(platform);
                    mCollideables.push_back(platform);
                }
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
        file << "platform: " << "ammocrate " << obj->getRenderPosition().x << " " << obj->getRenderPosition().y << "\n";
    }

    file.close();
}
