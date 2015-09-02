#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "HealthBar.h"
#include "Weapon.h"
#include "WorldRef.h"
#include "Quest.h"

class Player : public SpriteObject, public ICollideable
{
    public:
        Player(SpriteInfo& info, sf::Vector2f pos, WorldRef& worldRef);
        ~Player();

        void update();
        void draw(sf::RenderTarget& target, float alpha);
        void drawStationary(sf::RenderTarget& target);
        void handleEvents(sf::Event& event, WorldRef& worldRef);

        bool onContactBegin(std::weak_ptr<ICollideable> object, bool fromLeft, bool fromTop);
        void onContactEnd(std::weak_ptr<ICollideable> object);

        void respawn(sf::Vector2f pos);
        void kill(){mAlive=false; mHealth.mHP = -1;}
        void setPosition(sf::Vector2f pos){mPhysicsPosition=pos;}

        int getDirection(){return mDirection;}
        bool isGrounded(){return mGrounded;}
        Weapon& getWeapon(){return mWeapon;}
        sf::Vector2f getWeaponTarget(){return mWeaponTarget;}
        float getWeaponAngle(){return mWeaponAngle;}
        Quest& getQuest(){return mQuest;}

    private:
        float mRunSpeed;
        float mJumpSpeed;
        int mDirection; // direction player is facing -- for animations
        bool mGrounded; // touching the ground
        bool mJumping;
        float mFallDamageRate; // mVelocity.y/mFallDamageRate

        HealthBar mHealth;

        Weapon mWeapon;
        sf::Vector2f mMousePosition;
        sf::Vector2f mWeaponTarget;
        float mWeaponAngle;

        Quest mQuest;
};

#endif // PLAYER_H
