#include "SpriteObject.h"

#include <iostream>

SpriteObject::SpriteObject(SpriteInfo& info, sf::Vector2f pos, bool parallax) : IRenderable(),
    mSpriteInfo(info),
    mCurrentFrame(0), mFrameDelay(100.f), mLoopAnim(true), mStartFrame(0), mEndFrame(0), mFrameDir(1),
    mRenderPosition(pos),
    mParallaxable(parallax)
{
    mSprite = sf::Sprite(info.mTexture);
    mSprite.setPosition(pos);
    mRenderPosition = pos;
    mRotation = 0.f;
    mAlive = true;
}

SpriteObject::~SpriteObject()
{
    //dtor
}

void SpriteObject::update()
{
    mSprite.setPosition(mRenderPosition);
    mSprite.setRotation(mRotation);
}

void SpriteObject::draw(sf::RenderTarget& target, float alpha)
{
    if (mAnimClock.getElapsedTime().asMilliseconds() >= mFrameDelay &&
            (mLoopAnim || (mFrameDir == 1 && mCurrentFrame != mEndFrame) || (mFrameDir == -1 && mCurrentFrame != mStartFrame)))
    {
        mAnimClock.restart();
        mCurrentFrame += mFrameDir;

        if (mCurrentFrame > mEndFrame && mFrameDir == 1 && mLoopAnim)
            mCurrentFrame = mStartFrame;
        else if (mCurrentFrame < mStartFrame && mFrameDir == -1 && mLoopAnim)
            mCurrentFrame = mEndFrame;
    }

    // Calculate frame position
    if (mSpriteInfo.mFrames > 1)
    {
        int frameX = (mCurrentFrame%mSpriteInfo.mFramesPerRow)*mSpriteInfo.mFrameDim.x;
        int frameY = (mCurrentFrame/mSpriteInfo.mFramesPerRow)*mSpriteInfo.mFrameDim.y;

        mSprite.setTextureRect(sf::IntRect(frameX, frameY, mSpriteInfo.mFrameDim.x, mSpriteInfo.mFrameDim.y));
    }

    // Stop here
    //*****************************************************************************************
    target.draw(mSprite); // Rendahhh!!!!
}

void SpriteObject::setFrameLoop(int start, int stop, bool loop)
{
    mLoopAnim = loop;

    if (start == mStartFrame && stop == mEndFrame)
        return;

    if (start <= stop)
    {
        mStartFrame = start;
        mEndFrame = stop;
        mCurrentFrame = start;
        mFrameDir = 1;
    }
    else
    {
        mStartFrame = stop;
        mEndFrame = start;
        mCurrentFrame = start;
        mFrameDir = -1;
    }
}
