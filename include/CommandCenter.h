#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "SpriteObject.h"

class CommandCenter : public SpriteObject
{
    public:
        CommandCenter(SpriteInfo& info, sf::Vector2f pos);
        ~CommandCenter();

        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event, WorldRef& worldRef);

    private:
        sf::Vector2f mLocalMousePosition;
        sf::Vector2f mGlobalMousePosition;
};

#endif // COMMANDCENTER_H
