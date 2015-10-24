#include "VehicleWeapon.h"

VehicleWeapon::VehicleWeapon(SpriteInfo& info, int tag, sf::Vector2f posOnVehicle) : Weapon(info, tag),
    mPositionOnVehicle(posOnVehicle)
{
    //ctor
}

VehicleWeapon::~VehicleWeapon()
{
    //dtor
}
