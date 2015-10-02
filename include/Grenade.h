#ifndef GRENADE_H
#define GRENADE_H

#include "SpriteObject.h"
#include "ICollideable.h"

class Grenade : public SpriteObject, public ICollideable
{
    public:
        Grenade(SpriteInfo& info, sf::Vector2f pos);
        ~Grenade();
    protected:
    private:
};

#endif // GRENADE_H
