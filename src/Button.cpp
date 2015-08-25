#include "Button.h"

#include "EntityTags.h"

Button::Button(SpriteInfo& info, sf::Vector2f pos) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::BUTTON)
{
    //ctor
}

Button::~Button()
{
    //dtor
}
