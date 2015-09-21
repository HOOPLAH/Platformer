#include "Player.h"

#include <iostream>

#include "Assets.h"
#include "Constants.h"
#include "Direction.h"
#include "EntityTags.h"
#include "Projectile.h"

Player::Player(SpriteInfo& info, sf::Vector2f pos) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::PLAYER),
    mHealth(100.f, sf::Vector2f(30.f, 2.f), false),
    mWeapon(Assets::sprites["pistol"])
{
    //mSprite.setOrigin(getCenter());

    mRunSpeed = 3.f;
    mJumpSpeed = 5.5f;
    mDirection = Direction::STILL_RIGHT;
    mGrounded = false;
    mJumping = true;
    mPhysicsPosition = pos;
    mFallDamageRate = 10.f;
}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    SpriteObject::update();

    // animations
    if (!mGrounded) // above ground
    {
        if (mDirection == Direction::LEFT)
            setFrameLoop(33, 33);
        else if (mDirection == Direction::STILL_LEFT)
            setFrameLoop(35, 35);

        else if (mDirection == Direction::RIGHT)
            setFrameLoop(30, 30);
        else if (mDirection == Direction::STILL_RIGHT)
            setFrameLoop(32, 32);
    }
    else if (mGrounded) // walking on ground
    {
        if (mDirection == Direction::LEFT)
            setFrameLoop(12, 17);
        else if (mDirection == Direction::STILL_LEFT)
            setFrameLoop(0, 5);

        else if (mDirection == Direction::RIGHT)
            setFrameLoop(18, 23);
        else if (mDirection == Direction::STILL_RIGHT)
            setFrameLoop(6, 11);
    }

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, 0.f));
    if (mHealth.mHP <= 0.f)
    {
        kill();
    }

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;

    mWeapon.update();
    mWeapon.setPosition(mRenderPosition + getCenter());
    sf::Vector2f weapFirePoint = mWeapon.getRenderPosition()+mWeapon.getFirePoint();
    mWeaponAngle = atan2(mWeaponTarget.y - weapFirePoint.y, mWeaponTarget.x - weapFirePoint.x);
}

void Player::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);
    //mRenderPosition = mPhysicsPosition;

    mHealth.draw(target);
    mWeapon.draw(target, alpha);
    mWeaponTarget = target.mapPixelToCoords(sf::Vector2i(mMousePosition.x, mMousePosition.y));
}

void Player::drawStationary(sf::RenderTarget& target)
{
    std::string sWeaponText = std::to_string(mWeapon.getMagazines());
    sWeaponText.append("/");
    sWeaponText.append(std::to_string(mWeapon.getAmmo()));
    sf::Text weaponText(sWeaponText, Assets::fonts["8bit"].mFont);
    target.draw(weaponText); // magazine / ammo_in_magazine

    if (!mQuest.mActions.empty())
    {
        if (mQuest.mActions.top()->mTag == ActionTag::KILL)
        {
            auto action = std::static_pointer_cast<KillAction>(mQuest.mActions.top());

            std::string sActionText = "kill ";
            sActionText.append(std::to_string(action->mTotalKillCount - action->mKillsLeftCount));
            sActionText.append("/");
            sActionText.append(std::to_string(action->mTotalKillCount));

            sf::Text actionText(sActionText, Assets::fonts["8bit"].mFont);
            actionText.setPosition(sf::Vector2f(SCREEN_WIDTH - actionText.getGlobalBounds().width, 0.f));
            target.draw(actionText);
        }
        else if (mQuest.mActions.top()->mTag == ActionTag::COLLECT)
        {
            auto action = std::static_pointer_cast<CollectAction>(mQuest.mActions.top());

            std::string sActionText = "collect ";
            sActionText.append(std::to_string(action->mTotalCollectCount - action->mCollectLeftCount));
            sActionText.append("/");
            sActionText.append(std::to_string(action->mTotalCollectCount));

            sf::Text actionText(sActionText, Assets::fonts["8bit"].mFont);
            actionText.setPosition(sf::Vector2f(SCREEN_WIDTH - actionText.getGlobalBounds().width, 0.f));
            target.draw(actionText);
        }
    }
}

void Player::handleEvents(sf::Event& event, WorldRef& worldRef)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (mWeaponTarget.x < mRenderPosition.x)
            {
                if (mDirection != Direction::STILL_LEFT && mDirection != Direction::STILL_RIGHT) // moving
                    mDirection = Direction::LEFT;
                else // still
                    mDirection = Direction::STILL_LEFT;
            }
            else if (mWeaponTarget.x > mRenderPosition.x)
            {
                if (mDirection != Direction::STILL_LEFT && mDirection != Direction::STILL_RIGHT) // moving
                    mDirection = Direction::RIGHT;
                else // still
                    mDirection = Direction::STILL_RIGHT;
            }

            mWeapon.fire(mWeaponAngle, worldRef, mTag);
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        mMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space && !mJumping)
        {
            mJumping = true;
            mVelocity.y = 0.f;
            mVelocity.y -= mJumpSpeed;
            mGrounded = false;
        }
        if (event.key.code == sf::Keyboard::A)
        {
            mVelocity.x = -mRunSpeed;
            mDirection = Direction::LEFT;
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            mVelocity.x = mRunSpeed;
            mDirection = Direction::RIGHT;
        }
    }

    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::A)
        {
            mVelocity.x  = 0.f;
            mDirection = Direction::STILL_LEFT;
        }
        else if (event.key.code == sf::Keyboard::D)
        {
            mVelocity.x  = 0.f;
            mDirection = Direction::STILL_RIGHT;
        }

        if (event.key.code == sf::Keyboard::R)
        {
            mWeapon.reload();
        }
    }
}

void Player::respawn(sf::Vector2f pos)
{
    mHealth.mHP = mHealth.mMaxHP;
    mPhysicsPosition = pos;
    mVelocity = sf::Vector2f(0.f, 0.f);
    mAlive = true;
}

bool Player::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->isStatic() && fromTop)
    {
        if (mVelocity.y/mFallDamageRate > 1.f)
        {
            mHealth.mHP -= mVelocity.y; // terraria fall damage = 10(h - 400), where h = fall distance
            //mHealth.mActive = true;
            //mHealth.mActiveClock.restart();
        }

        mGrounded = true;
        mJumping = false;
    }

    else if (object.lock()->getTag() == EntityTags::PROJECTILE)
    {
        auto proj = static_cast<Projectile*>(&*object.lock());

        if (proj->getOwnerTag() != mTag)
        {
            mHealth.mHP -= proj->getDamage();
            //mHealth.mActive = true;
            //mHealth.mActiveClock.restart();

            proj->kill();

            if (mHealth.mHP <= 0.f)
            {
                kill();
            }
        }

        return false;
    }

    return true;
}

void Player::onContactEnd(std::weak_ptr<ICollideable> object)
{
}
