#ifndef ICOLLIDEABLE_H
#define ICOLLIDEABLE_H

#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "IObject.h"

class ICollideable : virtual public IObject
{
    public:
        ICollideable(sf::FloatRect hitbox, sf::Vector2f dim, int tag, bool _static=false) : IObject()
        {
            mHitBox = hitbox;
            mDimensions = dim;
            mTag = tag;
            mStatic = _static;
            mCollisionActive = true;
        }
        virtual ~ICollideable(){}

        virtual bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop){return true;}
        virtual void onContactEnd(std::weak_ptr<ICollideable> object){}

        // Mutators
        void setHitBox(sf::FloatRect hitbox){mHitBox=hitbox;}
        void setDimensions(sf::Vector2f dim){mDimensions=dim;}
        void setPhysicsPosition(sf::Vector2f pos){mPhysicsPosition=pos;}
        void setVelocity(sf::Vector2f vel){mVelocity = vel;}
        void setCollisionActive(bool active){mCollisionActive=active;}
        void setTag(int tag){mTag=tag;}

        // Accessors
        sf::FloatRect getHitBox(){return mHitBox;}
        sf::Vector2f getDimensions(){return mDimensions;}
        sf::Vector2f getPhysicsPosition(){return mPhysicsPosition;}
        sf::Vector2f getVelocity(){return mVelocity;}
        bool isStatic(){return mStatic;}
        bool isCollisionActive(){return mCollisionActive;}
        int getTag(){return mTag;}

    protected:
        sf::FloatRect mHitBox;
        sf::Vector2f mDimensions;
        sf::Vector2f mPhysicsPosition;
        sf::Vector2f mOldPhysicsPosition;
        sf::Vector2f mVelocity;
        bool mStatic;
        bool mCollisionActive;
        int mTag;
};

#endif // ICOLLIDEABLE_H
