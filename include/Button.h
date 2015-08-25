#ifndef BUTTON_H
#define BUTTON_H

#include "SpriteObject.h"
#include "ICollideable.h"

class Button : public SpriteObject, public ICollideable
{
    public:
        Button(SpriteInfo& info, sf::Vector2f pos);
        ~Button();

        void setPressed(bool pressed){mPressed=pressed;}
        bool isPressed(){return mPressed;}

    private:
        bool mPressed;
};

#endif // BUTTON_H
