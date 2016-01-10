#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "IRenderable.h"
#include "SpriteInfo.h"

class SpriteObject : public IRenderable
{
    public:
        SpriteObject(SpriteInfo& info, sf::Vector2f pos, bool parallax=false, bool stationary=false);
        virtual ~SpriteObject();

        virtual void update();
        virtual void draw(sf::RenderTarget& target, float alpha);

        // Mutator
        void setRenderPosition(sf::Vector2f pos){mSprite.setPosition(pos); mRenderPosition=pos;}
        virtual void setRotation(float rot){mRotation=rot; mSprite.setRotation(rot);}
        void setFrameLoop(int start, int stop, bool loop=true);
        void setFrameDelay(float delay){mFrameDelay=delay;}

        // Accessor
        SpriteInfo& getSpriteInfo(){return mSpriteInfo;}
        sf::Sprite& getSprite(){return mSprite;}
        sf::Vector2f getRenderPosition(){return mRenderPosition;}
        sf::Vector2f getOldRenderPosition(){return mOldRenderPosition;}
        sf::Vector2f getCenter(){return sf::Vector2f(mSpriteInfo.mFrameDim.x/2, mSpriteInfo.mFrameDim.y/2);}
        bool isParallaxable(){return mParallaxable;}
        bool isStationary(){return mStationary;}
        int getCurrentFrame(){return mCurrentFrame;}
        int getEndFrame(){return mEndFrame;}

    protected:
        SpriteInfo& mSpriteInfo;
        sf::Sprite mSprite;
        sf::Vector2f mRenderPosition;
        sf::Vector2f mOldRenderPosition;
        float mRotation;
        bool mParallaxable; // is this meant for parallax
        bool mStationary; // just a background object that doesn't move with camera

        int mCurrentFrame;
        sf::Clock mAnimClock;
        float mFrameDelay;
        bool mLoopAnim;
        int mStartFrame;
        int mEndFrame;
        int mFrameDir;
};

#endif // SPRITEOBJECT_H
