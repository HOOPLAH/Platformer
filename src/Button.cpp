#include "Button.h"

#include "EntityTags.h"

Button::Button(SpriteInfo& info, sf::Vector2f pos) :
    SpriteObject(info, pos)
{
    //ctor
}

Button::~Button()
{
    //dtor
}

void Button::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    if (mState == ButtonStates::Up)
        setFrameLoop(0, 0);
    else if (mState == ButtonStates::Down)
        setFrameLoop(1, 1);
    else if (mState == ButtonStates::Hover)
        setFrameLoop(2, 2);
}
