#include "Turret.h"

#include "Assets.h"
#include "EntityTags.h"

Turret::Turret(SpriteInfo& info, sf::Vector2f pos) : WorldObject(info, pos, EntityTags::TURRET, false, false),
    mWeapon(Assets::sprites["turrethead"])
{
    mWeapon.setUnlimitedAmmo(true);
    mWeapon.setRange(300.f);
    mWeapon.setDamage(1.f);
    mWeapon.setFirePoint(sf::Vector2f(20.f, 3.f));
    mWeapon.getSprite().setOrigin(mWeapon.getCenter());
    mWeaponAngle = 0.f;

    mOwnerTag = EntityTags::TURRET;
}

Turret::~Turret()
{
    //dtor
}

void Turret::update(WorldRef& worldRef)
{
    WorldObject::update();

    auto closeObjs = worldRef.getObjectsWithinArea(sf::FloatRect(mWeapon.getRenderPosition(), sf::Vector2f(mWeapon.getRange(), mWeapon.getRange())));
    for (auto obj : closeObjs)
    {
        if (obj.lock()->getTag() == EntityTags::PLAYER)
            mWeaponTarget = obj;
    }

    mWeapon.update();
    mWeapon.setPosition(mRenderPosition + sf::Vector2f(34.f, -10.f));
    sf::Vector2f weapFirePoint = (mWeapon.getRenderPosition()+mWeapon.getFirePoint());
    if (!mWeaponTarget.expired())
    {
        mWeaponAngle = atan2((mWeaponTarget.lock()->getPhysicsPosition().y+mWeaponTarget.lock()->getDimensions().y/2) - weapFirePoint.y,
                             (mWeaponTarget.lock()->getPhysicsPosition().x+mWeaponTarget.lock()->getDimensions().x/2) - weapFirePoint.x);
        mWeapon.fire(mWeaponAngle, worldRef, mOwnerTag);
    }

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, -30.f));
}

void Turret::draw(sf::RenderTarget& target, float alpha)
{
    WorldObject::draw(target, alpha);

    mHealth.draw(target);
    mWeapon.draw(target, alpha);
    mWeapon.setRotation(mWeaponAngle*RADTODEG);
}

bool Turret::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::TURRET || object.lock()->getTag() == EntityTags::PLAYER)
        return false;
    else if (object.lock()->getTag() == EntityTags::PROJECTILE)
    {
        auto proj = static_cast<Projectile*>(&*object.lock());

        if (proj->getOwnerTag() != mOwnerTag)
        {
            if (mHealth.mActive)
            {
                mHealth.mHP -= proj->getDamage();
                mHealth.mActiveClock.restart();
            }
            proj->kill();
        }

        return false;
    }

    return true;
}
