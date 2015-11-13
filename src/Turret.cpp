#include "Turret.h"

#include "Assets.h"
#include "EntityTags.h"

Turret::Turret(SpriteInfo& info, sf::Vector2f pos) : Vehicle(info, pos),
    mWeapon(Assets::sprites["turrethead"], EntityTags::TURRET),
    mHealth(100.f, sf::Vector2f(30.f, 2.f), false)
{
    mAutoAim = true;

    mWeapon.setUnlimitedAmmo(true);
    mWeapon.setRange(300.f);
    mWeapon.setDamage(1.f);
    mWeapon.setFirePoint(sf::Vector2f(20.f, 3.f));
    mWeapon.getSprite().setOrigin(mWeapon.getCenter());
    mWeaponAngle = 0.f;

    mTag = EntityTags::VEHICLE;
    mOwnerTag = EntityTags::TURRET;
}

Turret::~Turret()
{
    //dtor
}

void Turret::update(WorldRef& worldRef)
{
    Vehicle::update(worldRef);

    if (mAutoAim)
    {
        mWeaponTarget = worldRef.getClosestObject(EntityTags::NPC, mRenderPosition);
        mWeapon.update();
        mWeapon.setFiringAngle(mWeaponAngle);
        mWeapon.setPosition(mRenderPosition + sf::Vector2f(34.f, -10.f));
        sf::Vector2f weapFirePoint = (mWeapon.getRenderPosition()+mWeapon.getFirePoint());
        if (!mWeaponTarget.expired())
        {
            mWeaponAngle = atan2((mWeaponTarget.lock()->getPhysicsPosition().y+mWeaponTarget.lock()->getDimensions().y/2) - weapFirePoint.y,
                                 (mWeaponTarget.lock()->getPhysicsPosition().x+mWeaponTarget.lock()->getDimensions().x/2) - weapFirePoint.x);
            mWeapon.fire(worldRef);
        }
    }

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, -30.f));
    if (mHealth.mHP <= 0.f)
        kill();
}

void Turret::draw(sf::RenderTarget& target, float alpha)
{
    Vehicle::draw(target, alpha);

    mHealth.draw(target);
    mWeapon.draw(target, alpha);
    mWeapon.setRotation(mWeaponAngle*RADTODEG);
}

void Turret::handleEvents(sf::Event& event, WorldRef& worldRef)
{
}

bool Turret::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::TURRET || object.lock()->getTag() == EntityTags::PLAYER ||
        object.lock()->getTag() == EntityTags::NPC || object.lock()->getTag() == EntityTags::GRENADE)
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
