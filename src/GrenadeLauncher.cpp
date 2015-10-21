#include "GrenadeLauncher.h"

#include "Assets.h"
#include "Grenade.h"
#include "EntityTags.h"
#include "FuncUtils.h"

GrenadeLauncher::GrenadeLauncher(SpriteInfo& info, int tag) : Weapon(info, tag)
{
    //ctor
}

GrenadeLauncher::~GrenadeLauncher()
{
    //dtor
}

void GrenadeLauncher::fire(WorldRef& worldRef)
{
    if (!checkAmmo())
        return;

    int dir = 1;
    if (std::abs(mFiringAngle*RADTODEG) > 90.f)
        dir = -1;

    sf::Vector2f firePoint = mFirePoint;
    rotateVec(firePoint, mFiringAngle*RADTODEG);

    auto start = mRenderPosition+sf::Vector2f(firePoint.x*dir, firePoint.y);
    auto grenade = std::make_shared<Grenade>(Assets::sprites["grenade"], start, mOwnerTag);
    grenade->setFiringAngle(mFiringAngle);
    grenade->setVelocity(sf::Vector2f(cos(mFiringAngle), sin(mFiringAngle))*grenade->getSpeed());
    grenade->setTag(EntityTags::GRENADE);
    worldRef.addCollideable(grenade);
    worldRef.addRenderable(grenade);
}
