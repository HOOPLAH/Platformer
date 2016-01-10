#ifndef ENTITYTAGS_H_INCLUDED
#define ENTITYTAGS_H_INCLUDED

namespace EntityTags
{
    enum
    {
        PLAYER=0,
        NPC=1,
        PLATFORM=2,
        PROJECTILE=4,
        WEAPON=8,
        GRENADE=16,
        VEHICLE=32,
        TURRET=64,
        LADDER=128,
        COLLECTIBLE=256
    };
}

#endif // ENTITYTAGS_H_INCLUDED
