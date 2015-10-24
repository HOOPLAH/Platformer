#ifndef VEHICLEWEAPON_H
#define VEHICLEWEAPON_H

#include "Weapon.h"

class VehicleWeapon : public Weapon
{
    public:
        VehicleWeapon(SpriteInfo& info, int tag, sf::Vector2f posOnVehicle);
        ~VehicleWeapon();

        sf::Vector2f getPositionOnVehicle(){return mPositionOnVehicle;}

    protected:
        sf::Vector2f mPositionOnVehicle;
};

#endif // VEHICLEWEAPON_H
