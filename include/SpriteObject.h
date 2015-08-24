#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "IRenderable.h"
#include "SpriteInfo.h"

class SpriteObject : public IRenderable
{
    public:
        SpriteObject(SpriteInfo& info, sf::Vector2f pos);
        virtual ~SpriteObject();

        virtual void update();
        virtual void draw(sf::RenderTarget& target, float alpha);

        // Mutator
        virtual void setPosition(sf::Vector2f pos){mRenderPosition=pos;}
        void setFrameLoop(int start, int stop, bool loop=true);

        // Accessor
        SpriteInfo getSpriteInfo(){return mSpriteInfo;}
        sf::Sprite& getSprite(){return mSprite;}
        sf::Vector2f getRenderPosition(){return mRenderPosition;}
        sf::Vector2f getOldRenderPosition(){return mOldRenderPosition;}
        sf::Vector2f getCenter(){return sf::Vector2f(mSpriteInfo.mFrameDim.x/2, mSpriteInfo.mFrameDim.y/2);}

    protected:
        SpriteInfo& mSpriteInfo;
        sf::Sprite mSprite;
        sf::Vector2f mRenderPosition;
        sf::Vector2f mOldRenderPosition;

        int mCurrentFrame;
        sf::Clock mAnimClock;
        float mFrameDelay;
        bool mLoopAnim;
        int mStartFrame;
        int mEndFrame;
        int mFrameDir;
};

#endif // SPRITEOBJECT_H

