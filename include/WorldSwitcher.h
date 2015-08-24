#ifndef WORLDSWITCHER_H
#define WORLDSWITCHER_H

#include "SpriteObject.h"
#include "ICollideable.h"

class WorldSwitcher : public SpriteObject, public ICollideable
{
    public:
        WorldSwitcher(SpriteInfo& info, sf::Vector2f pos, std::string nextWorld);
        ~WorldSwitcher();

        void update();

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);

        void setPressed(bool pressed){mPressed=pressed;}
        bool isPressed(){return mPressed;}

        std::string getNextWorld(){return mNextWorld;}

    private:
        bool mPressed;

        std::string mNextWorld; // which world to go to if im pressed
};

#endif // WORLDSWITCHER_H
