#include "Weapon.h"

#include <memory>
#include <iostream>

#include "Assets.h"
#include "Constants.h"
#include "FuncUtils.h"
#include "EntityTags.h"

Weapon::Weapon(SpriteInfo& info) : SpriteObject(info, sf::Vector2f(0.f, 0.f))
{
    mDamage = 10;
    mRange = 500.f;
    mInaccuracy = 0.5f;
    mCoolDown = 100;
    mFirePoint = sf::Vector2f(10.f, 0.f);

    mMaxAmmo = 10;
    mMaxMagazines = 10;
    mAmmo = mMaxAmmo;
    mMagazines = 3;
    mUnlimitedAmmo = false;
}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::update()
{
    SpriteObject::update();
}

void Weapon::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);
}

void Weapon::fire(float angle, WorldRef& worldRef, int ownerTag)
{
    if (mCoolDownClock.getElapsedTime().asMilliseconds() < mCoolDown) //not cooled down yet, don't fire
        return;

    if (mAmmo <= 0 && !mUnlimitedAmmo)
    {
        if (mMagazines > 0) // should reload
        {
            mAmmo = mMaxAmmo;
            mMagazines--;
        }
        else
            return;
    }

    mCoolDownClock.restart();
    if (!mUnlimitedAmmo)
        mAmmo--;

    angle *= RADTODEG;
    //angle += (((float)(rand()%100)/100.f)*(mInaccuracy/2))-(mInaccuracy/2);
    angle *= DEGTORAD;

    int dir = 1;
    if (std::abs(angle*RADTODEG) > 90.f)
        dir = -1;

    sf::Vector2f firePoint = mFirePoint;
    rotateVec(firePoint, angle*RADTODEG);

    auto start = mRenderPosition+sf::Vector2f(firePoint.x*dir, firePoint.y);
    auto proj = std::make_shared<Projectile>(Assets::sprites["bullet"], start, mDamage, mRange, ownerTag);
    proj->setFiringAngle(angle);
    worldRef.addProjectile(proj);
}

void Weapon::addAmmo(int ammo)
{
    int surplus = std::abs(mMaxAmmo - mAmmo - ammo);

    if (mMaxAmmo < (mAmmo + ammo))
    {
        if (mMagazines+1 < mMaxMagazines)
        {
            mMagazines++;
            mAmmo = surplus;
        }
        else
        {
            mMagazines = mMaxMagazines;
            mAmmo = mMaxAmmo;
        }
    }
    else
    {
        mAmmo += ammo;
    }
}
