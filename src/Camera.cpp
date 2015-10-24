#include "Camera.h"

#include <iostream>

#include "Constants.h"

Camera::Camera()
{
    mView = sf::View(sf::FloatRect(mCenter.x, mCenter.y, SCREEN_WIDTH, SCREEN_HEIGHT));
}

Camera::~Camera()
{
    //dtor
}

void Camera::moveTo(sf::Vector2f newCenter)
{
    /*float dist = sqrt(pow(mOldCenter.x - mCenter.x, 2) + pow(mOldCenter.y - mCenter.y, 2));

    if (dist > 5.f)
    {
        float angle = atan2(mOldCenter.y - mCenter.y, mOldCenter.x - mCenter.x);
        sf::Vector2f vel = sf::Vector2f(cos(angle), sin(angle))*50.f;
        mCenter += vel;
    }*/

    mCenter = newCenter;

    mView.setCenter(mCenter);
}

void Camera::follow(sf::Vector2f center)
{
    mOldCenter = mCenter;
    mCenter = center;

    moveTo(mCenter);
}
