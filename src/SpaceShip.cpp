#include "SpaceShip.h"

#include "EntityTags.h"

#include <Projectile.h>

SpaceShip::SpaceShip(SpriteInfo& info, sf::Vector2f pos) : SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::SPACESHIP)
{
    mAcceleration = 6.f;
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
}

void SpaceShip::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);
}

void SpaceShip::handleEvents(sf::Event& event, WorldRef& worldRef)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            // fire weapons
        }
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
            mSprite.setScale(-1.f, 1.f);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            mVelocity.x = mAcceleration;
            mSprite.setScale(1.f, 1.f);
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

    return true;
}

void SpaceShip::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
