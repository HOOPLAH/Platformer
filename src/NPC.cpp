#include "NPC.h"

#include <iostream>
#include <cstdlib>

#include "Assets.h"
#include "Constants.h"
#include "Direction.h"
#include "EntityTags.h"
#include "Projectile.h"
#include "AIFollowModule.h"

#include "FuncUtils.h"

NPC::NPC(SpriteInfo& info, sf::Vector2f pos, WorldRef& worldRef) :
    SpriteObject(info, pos),
    ICollideable(info.mHitBox, info.mFrameDim, EntityTags::NPC),
    mHealth(25.f, sf::Vector2f(30.f, 2.f)),
    mWeapon(Assets::sprites["pistol"], EntityTags::NPC),
    mTarget(*worldRef.getHero().lock())
{
    mSpawnPoint = pos;
    mRunSpeed = 2.f;
    mJumpSpeed = 5.5f;
    mDirection = Direction::STILL_LEFT;
    mGrounded = false;
    mJumping = true;
    mPhysicsPosition = pos;

    mAI = std::make_unique<AIFollowModule>(*this);

    mWeapon.setCoolDown(500);
    mWeaponAngle = 0.f;
    mKillerTag = -1;

    mNeedToUpdatePath = true;
}

NPC::~NPC()
{
    //dtor
}

void NPC::update(WorldRef& worldRef)
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

        if (mDirection == Direction::RIGHT)
            setFrameLoop(18, 23);
        else if (mDirection == Direction::STILL_RIGHT)
            setFrameLoop(6, 11);
    }

    mHealth.setPosition(mRenderPosition + sf::Vector2f(getCenter().x, 0.f));
    if (mHealth.mHP <= 0.f)
    {
        kill();
    }

    mAI->update(worldRef);

    mOldPhysicsPosition = mPhysicsPosition;
    mPhysicsPosition += mVelocity;

    mWeapon.update();
    mWeapon.setFiringAngle(mWeaponAngle);
    mWeapon.setPosition(mRenderPosition + getCenter());
    //mTarget = worldRef.getHero();
    mWeaponAngle = atan2(mTarget.getRenderPosition().y - mRenderPosition.y,
                         mTarget.getRenderPosition().x - mRenderPosition.x);
}

void NPC::draw(sf::RenderTarget& target, float alpha)
{
    SpriteObject::draw(target, alpha);

    mOldRenderPosition = mRenderPosition;
    mRenderPosition = mPhysicsPosition*alpha + mOldPhysicsPosition*(1.f - alpha);

    /*sf::FloatRect rect;
    sf::Vector2f pos;

    if (mRenderPosition.y - mTarget.getRenderPosition().y > -1.f)
    {
        // target is left and above
        if (mTarget.getRenderPosition().x < mRenderPosition.x)
        {
            rect = sf::FloatRect(sf::Vector2f(0.f, 0.f), (mRenderPosition+sf::Vector2f(mHitBox.width*1.6, mHitBox.height*1.1)) -
                                (mTarget.getRenderPosition()+sf::Vector2f(mTarget.getHitBox().left, mTarget.getHitBox().top)));
            pos = mTarget.getRenderPosition()+sf::Vector2f(mTarget.getHitBox().left, mTarget.getHitBox().top);
        }
        // right and above
        if (mTarget.getRenderPosition().x > mRenderPosition.x)
        {
            rect = sf::FloatRect(sf::Vector2f(0.f, 0.f),
                                (mTarget.getRenderPosition()+sf::Vector2f(mTarget.getHitBox().width*1.6, mTarget.getHitBox().top*1.1)) -
                                (mRenderPosition+sf::Vector2f(mHitBox.left, mHitBox.height)));
            pos = mRenderPosition+sf::Vector2f(mHitBox.left, mHitBox.height);
        }
    }
    else
    {
        // target is left and below
        if (mTarget.getRenderPosition().x < mRenderPosition.x)
        {
            rect = sf::FloatRect(sf::Vector2f(0.f, 0.f), (mRenderPosition+sf::Vector2f(mHitBox.width*1.6, mHitBox.top*1.1)) -
                                (mTarget.getRenderPosition()+sf::Vector2f(mTarget.getHitBox().left, mTarget.getHitBox().height)));
            pos = mTarget.getRenderPosition()+sf::Vector2f(mTarget.getHitBox().left, mTarget.getHitBox().height);
        }
        // right and below
        if (mTarget.getRenderPosition().x > mRenderPosition.x)
        {
            rect = sf::FloatRect(sf::Vector2f(0.f, 0.f),
                                (mTarget.getRenderPosition()+sf::Vector2f(mTarget.getHitBox().width*1.6, mTarget.getHitBox().height*1.1)) -
                                (mRenderPosition+sf::Vector2f(mHitBox.left, mHitBox.top)));
            pos = mRenderPosition+sf::Vector2f(mHitBox.left, mHitBox.top);
        }
    }

    sf::RectangleShape box(sf::Vector2f(rect.width, rect.height));
    box.setOutlineThickness(1.f);
    box.setOutlineColor(sf::Color::Yellow);
    box.setFillColor(sf::Color::Transparent);
    box.setPosition(pos);*/

    mHealth.draw(target);
    mWeapon.draw(target, alpha);
}

bool NPC::onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop)
{
    if (object.lock()->getTag() == EntityTags::PLATFORM && fromTop)
    {
        mGrounded = true;
        mJumping = false;
    }
    else if (object.lock()->getTag() == EntityTags::PLAYER || object.lock()->getTag() == EntityTags::NPC)
    {
        return false;
    }
    else if (object.lock()->getTag() == EntityTags::PROJECTILE)
    {
        auto proj = static_cast<Projectile*>(&*object.lock());

        if (proj->getOwnerTag() != mTag)
        {
            proj->kill();
            mKillerTag = proj->getOwnerTag();
            mHealth.mHP -= proj->getDamage();
            mHealth.mActive = true;
            mHealth.mActiveClock.restart();
        }

        return false;
    }

    return true;
}

void NPC::onContactEnd(std::weak_ptr<ICollideable> object)
{
}

bool NPC::walk(sf::Vector2f pos)
{
    if (length(pos - getFeetPosition()) > 30.f)
    {
        if (pos.x > mRenderPosition.x) // to the right
        {
            mDirection = Direction::RIGHT;
            mVelocity.x = mRunSpeed;
        }
        else if (pos.x < mRenderPosition.x) // to the left
        {
            mDirection = Direction::LEFT;
            mVelocity.x = -mRunSpeed;
        }
    }
    else
    {
        //stop();
        return true;
    }

    return false;
}

void NPC::stop()
{
    if (mDirection == Direction::LEFT)
        mDirection = Direction::STILL_LEFT;
    else if (mDirection == Direction::RIGHT)
        mDirection = Direction::STILL_RIGHT;

    mVelocity = sf::Vector2f(0.f, mVelocity.y);
}

void NPC::jump(int dir)
{
    if (mJumping)
        return;

    if (!mJumping)
    {
        mVelocity.y -= mJumpSpeed;
        mJumping = true;
        mGrounded = false;

        if (dir == Direction::LEFT)
            mVelocity.x =-mRunSpeed;
        else if (dir == Direction::RIGHT)
            mVelocity.x = mRunSpeed;
    }
}

void NPC::respawn()
{
    mHealth.mHP = mHealth.mMaxHP;
    mPhysicsPosition = mSpawnPoint;
    mVelocity = sf::Vector2f(0.f, 0.f);
    mAlive = true;
}
