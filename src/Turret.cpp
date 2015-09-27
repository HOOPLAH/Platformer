#include "Turret.h"

#include "Assets.h"
#include "EntityTags.h"

Turret::Turret(SpriteInfo& info, sf::Vector2f pos) : WorldObject(info, pos, EntityTags::TURRET),
    mWeapon(Assets::sprites["turrethead"])
{
    mWeapon.setUnlimitedAmmo(true);
    mWeapon.setFirePoint(sf::Vector2f(60.f, 13.f));
    mWeaponAngle = 0.f;
    mOwnerTag = EntityTags::PLAYER;
    mHealth.mActive = false;
}

Turret::~Turret()
{
    //dtor
}

void Turret::update(WorldRef& worldRef)
{
    WorldObject::update();

    mWeapon.update();
    mWeapon.setPosition(mRenderPosition + sf::Vector2f(0.f, -24.f));
    sf::Vector2f weapFirePoint = mWeapon.getRenderPosition()+mWeapon.getFirePoint();
    mWeaponAngle = atan2(mWeaponTarget.y - weapFirePoint.y, mWeaponTarget.x - weapFirePoint.x);
    mWeapon.fire(0.f, worldRef, mOwnerTag);
}

void Turret::draw(sf::RenderTarget& target, float alpha)
{
    WorldObject::draw(target, alpha);

    mHealth.draw(target);
    mWeapon.draw(target, alpha);
    mWeapon.setRotation(mWeaponAngle);
}
