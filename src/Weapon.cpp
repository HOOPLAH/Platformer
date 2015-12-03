#include "Weapon.h"

#include <memory>
#include <iostream>

#include "Assets.h"
#include "Constants.h"
#include "FuncUtils.h"
#include "EntityTags.h"

Weapon::Weapon(SpriteInfo& info, int tag) : Item(info, "Weapon")
{
    mDamage = 10;
    mRange = 500.f;
    mInaccuracy = 0.5f;
    mCoolDown = 100;
    mOwnerTag = tag;
    mFirePoint = sf::Vector2f(10.f, 0.f);

    mMaxAmmo = 10;
    mMaxMagazines = 10;
    mAmmo = mMaxAmmo;
    mMagazines = 3;
    mUnlimitedAmmo = true;
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

void Weapon::use(WorldRef& worldRef)
{
    fire(worldRef);
}

bool Weapon::checkAmmo()
{
    if (mCoolDownClock.getElapsedTime().asMilliseconds() < mCoolDown) //not cooled down yet, don't fire
        return false;

    if (mAmmo <= 0 && !mUnlimitedAmmo)
    {
        if (mMagazines > 0) // should reload
        {
            mAmmo = mMaxAmmo;
            mMagazines--;
        }
        else
            return false;
    }

    mCoolDownClock.restart();
    if (!mUnlimitedAmmo)
        mAmmo--;

    return true;
}

void Weapon::fire(WorldRef& worldRef)
{
    if (!checkAmmo())
        return;

    // make this weapon inaccurate
    /*mFiringAngle *= RADTODEG;
    angle += (((float)(rand()%100)/100.f)*(mInaccuracy/2))-(mInaccuracy/2);
    mFiringAngle *= DEGTORAD;*/

    int dir = 1;
    if (std::abs(mFiringAngle*RADTODEG) > 90.f)
        dir = -1;

    sf::Vector2f firePoint = mFirePoint;
    rotateVec(firePoint, mFiringAngle*RADTODEG);

    auto start = mRenderPosition+sf::Vector2f(firePoint.x, firePoint.y);
    auto proj = std::make_shared<Projectile>(Assets::sprites["bullet"], start, mDamage, mRange, mOwnerTag);
    proj->setRotation(mFiringAngle*RADTODEG);
    proj->setFiringAngle(mFiringAngle);
    worldRef.addCollideable(proj);
    worldRef.addRenderable(proj);
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
