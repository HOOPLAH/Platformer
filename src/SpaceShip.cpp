#include "SpaceShip.h"

#include "Assets.h"
#include "EntityTags.h"

SpaceShip::SpaceShip(SpriteInfo& info, sf::Vector2f pos) : SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::VEHICLE)
{
    mAcceleration = 6.f;

    mWeaponAngle = 0.f;
    Weapon weap1(Assets::sprites["nothing"], EntityTags::VEHICLE);
    weap1.setFirePoint(sf::Vector2f(0, 0));

    Weapon weap2(Assets::sprites["nothing"], EntityTags::VEHICLE);
    weap2.setFirePoint(sf::Vector2f(143, 20));

    mWeapons.push_back(weap1);
    //mWeapons.push_back(weap2);
}

SpaceShip::~SpaceShip()
{
    //dtor
}

void SpaceShip::update(WorldRef& worldRef)
{
    SpriteObject::update();

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;

    for (auto& weap : mWeapons)
    {
        sf::Vector2f weapFirePoint = mRenderPosition+weap.getFirePoint();
        mWeaponAngle = atan2(mWeaponTarget.y - weapFirePoint.y, mWeaponTarget.x - weapFirePoint.x);

        weap.setFiringAngle(mWeaponAngle);
        weap.setPosition(mRenderPosition+sf::Vector2f(0, 20));
    }
}

void SpaceShip::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);
    mWeaponTarget = target.mapPixelToCoords(sf::Vector2i(mMousePosition.x, mMousePosition.y));
}

void SpaceShip::handleEvents(sf::Event& event, WorldRef& worldRef)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            mVelocity.y = -mAcceleration;
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            mVelocity.y = mAcceleration;
        }

        if (event.key.code == sf::Keyboard::A)
        {
            mVelocity.x = -mAcceleration;
            setFrameLoop(0, 0);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            mVelocity.x = mAcceleration;
            setFrameLoop(1, 1);
        }
    }

    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
        {
            /*if (mVelocity.y < 0.f)
                mVelocity.y += mAcceleration;
            else if (mVelocity.y > 0.f)
                mVelocity.y -= mAcceleration;*/

            mVelocity.y = 0;
        }

        else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
        {
            /*if (mVelocity.x < 0.f)
                mVelocity.x += mAcceleration;
            else if (mVelocity.x > 0.f)
                mVelocity.x -= mAcceleration;*/

            mVelocity.x = 0;
        }
    }

    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (auto& weap : mWeapons)
            {
                weap.fire(worldRef);
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        mMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    }
}

bool SpaceShip::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::PROJECTILE)
    {
        auto proj = static_cast<Projectile*>(&*object.lock());

        if (proj->getOwnerTag() != mTag)
        {
            //mHealth.mHP -= proj->getDamage();
            //mHealth.mActive = true;
            //mHealth.mActiveClock.restart();

            proj->kill();
        }

        return false;
    }
    else if (object.lock()->getTag() == EntityTags::PLAYER || object.lock()->getTag() == EntityTags::NPC ||
             object.lock()->getTag() == EntityTags::TURRET)
         {
            return false;
         }

    return true;
}

void SpaceShip::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
