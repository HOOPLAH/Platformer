#ifndef ITEM_H
#define ITEM_H

#include "SpriteObject.h"

#include "WorldRef.h"

class Item : public SpriteObject
{
    public:
        Item(SpriteInfo& info, std::string name, sf::Vector2f pos = sf::Vector2f());
        virtual ~Item();

        virtual void use(WorldRef& worldRef){}
        virtual void update(){SpriteObject::update();}
        virtual void draw(sf::RenderTarget& target, float alpha){SpriteObject::draw(target, alpha);}

        std::string getName(){return mName;}

    protected:
        std::string mName;
};

#endif // ITEM_H
