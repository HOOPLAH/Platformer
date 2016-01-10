#include "Turret.h"

#include "Assets.h"
#include "EntityTags.h"

Turret::Turret(SpriteInfo& info, sf::Vector2f pos) : Vehicle(info, pos),
    mWeapon(Assets::sprites["turrethead"], EntityTags::TURRET),
    mHealth(100.f, sf::Vector2f(30.f, 2.f), false)
{
    mAutoAim = false;

    mWeapon.setUnlimitedAmmo(true);
    mWeapon.setRange(300.f);
    mWeapon.setDamage(1.f);
    mWeapon.setFirePoint(sf::Vector2f(20.f, 3.f));
    mWeapon.getSprite().setOrigin(mWeapon.getCenter());
    mWeaponAngle = 0.f;

    mTag = (EntityTags::VEHICLE|EntityTags::TURRET);
    mOwnerTag = EntityTags::TURRET;
}

Turret::~Turret()
{
    //dtor
}

void Turret::update(WorldRef& worldRef)
{
    Vehicle::update(worldRef);

    if (!mInVehicle && mAutoAim)
    {
        auto obj = worldRef.getClosestObject(EntityTags::NPC, mRenderPosition);
        mWeaponTarget = obj.lock()->getPhysicsPosition();// + (obj.lock()->getDimensions()/2);
        mWeapon.update();
        mWeapon.fire(worldRef);
    }
    else if (mInVehicle)
    {
        sf::Vector2f weapFirePoint = (mWeapon.getRenderPosition()+mWeapon.getFirePoint());
        mWeaponAngle = atan2(mWeaponTarget.y - weapFirePoint.y, mWeaponTarget.x - weapFirePoint.x);
    }

    mWeapon.setFiringAngle(mWeaponAngle);

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, -30.f));
    mWeapon.setRenderPosition(mRenderPosition + sf::Vector2f(34.f, -5.f));
    if (mHealth.mHP <= 0.f)
        kill();
}

void Turret::draw(sf::RenderTarget& target, float alpha)
{
    Vehicle::draw(target, alpha);

    mHealth.draw(target);
    mWeapon.draw(target, alpha);
    mWeapon.setRotation(mWeaponAngle*RADTODEG);
    mWeaponTarget = target.mapPixelToCoords(sf::Vector2i(mMousePosition.x, mMousePosition.y));
}

void Turret::handleEvents(sf::Event& event, WorldRef& worldRef)
{
    if (event.type == sf::Event::MouseMoved)
    {
        mMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            mWeapon.fire(worldRef);
        }
    }
}

bool Turret::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::PLAYER ||
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
