#ifndef HEALTHBAR_H_INCLUDED
#define HEALTHBAR_H_INCLUDED

#include <SFML/Graphics.hpp>

struct HealthBar
{
    HealthBar(float hp, sf::Vector2f dim, bool hideHealth=true)
    {
        mHP = hp;
        mMaxHP = hp;
        mFullDimensions = dim;

        mBar = sf::RectangleShape(mFullDimensions);
        mBar.setOrigin(mFullDimensions.x/2, mFullDimensions.y/2);

        mActive = true;
        mHideHealth = hideHealth;
        mActiveTime = 2;
    }

    void draw(sf::RenderTarget& target)
    {
        float ratio = mHP/mMaxHP;
        mBar.setSize(sf::Vector2f(mFullDimensions.x*ratio, mFullDimensions.y));

        if (mActiveClock.getElapsedTime().asSeconds() > mActiveTime && mHideHealth)
            mActive = false;

        if (ratio >= 0.55f)
            mBar.setFillColor(sf::Color::Green);
        else if (ratio < 0.55f && ratio >= 0.25f)
            mBar.setFillColor(sf::Color(255.f, 140.f, 0.f, 255.f)); // orange
        else if (ratio < 0.25f)
            mBar.setFillColor(sf::Color::Red);

        if (mActive)
            target.draw(mBar);
    }

    void setPosition(sf::Vector2f pos)
    {
        mBar.setPosition(pos);
    }

    float mHP;
    float mMaxHP;
    sf::Vector2f mFullDimensions;
    sf::RectangleShape mBar;

    bool mActive;
    sf::Clock mActiveClock;
    int mActiveTime;
    bool mHideHealth;
};

#endif // HEALTHBAR_H_INCLUDED
