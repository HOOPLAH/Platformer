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
        Button(SpriteInfo& info, sf::Vector2f pos, std::string label="");
        ~Button();

        void update();
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

        void setPressed(bool pressed){mPressed=pressed;}
        void setState(int state){mState=state;}
        void setLabel(std::string label){mLabel=label; mText.setString(label);}

        bool isPressed(){return mPressed;}
        int getState(){return mState;}
        std::string getLabel(){return mLabel;}

    private:
        bool mPressed;
        int mState;

        std::string mLabel;
        sf::Text mText;

        sf::Vector2f mMousePosition;
};

#endif // BUTTON_H
