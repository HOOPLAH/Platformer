#include "CommandCenter.h"

#include "Assets.h"
#include "NPC.h"

CommandCenter::CommandCenter(SpriteInfo& info, sf::Vector2f pos) : SpriteObject(info, pos)
{
    //ctor
}

CommandCenter::~CommandCenter()
{
    //dtor
}

void CommandCenter::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mGlobalMousePosition = target.mapPixelToCoords(sf::Vector2i(mLocalMousePosition.x, mLocalMousePosition.y));
}

void CommandCenter::handleEvents(sf::Event& event, WorldRef& worldRef)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            if (sf::FloatRect(mRenderPosition, sf::Vector2f(mSpriteInfo.mHitBox.width, mSpriteInfo.mHitBox.height)).contains(mGlobalMousePosition))
            {
                auto npc = std::make_shared<NPC>(Assets::sprites["pinkpeewee"], mRenderPosition, worldRef);
                worldRef.addRenderable(npc);
                worldRef.addCollideable(npc);
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        mLocalMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    }
}
