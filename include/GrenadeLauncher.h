#ifndef GRENADELAUNCHER_H
#define GRENADELAUNCHER_H

#include "Weapon.h"

class GrenadeLauncher : public Weapon
{
    public:
        GrenadeLauncher(SpriteInfo& info, int tag);
        ~GrenadeLauncher();

        void fire(WorldRef& ref);

    private:
};

#endif // GRENADELAUNCHER_H
