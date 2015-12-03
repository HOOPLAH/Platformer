#ifndef BUTTON_H
#define BUTTON_H

#include "SpriteObject.h"

namespace ButtonStates
{
    enum
    {
        Up,
        Down,
        Hover
    };
}

class Button : public SpriteObject
{
    public:
        Button(SpriteInfo& info, sf::Vector2f pos);
        ~Button();

        void draw(sf::RenderTarget& target, float alpha);

        void setPressed(bool pressed){mPressed=pressed;}
        bool isPressed(){return mPressed;}

        void setState(int state){mState=state;}
        int getState(){return mState;}

    private:
        bool mPressed;
        int mState;
};

#endif // BUTTON_H
