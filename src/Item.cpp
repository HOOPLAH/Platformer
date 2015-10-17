#include "Item.h"

Item::Item(SpriteInfo& info, std::string name, sf::Vector2f pos) : SpriteObject(info, pos),
    mName(name)
{
    //ctor
}

Item::~Item()
{
    //dtor
}
