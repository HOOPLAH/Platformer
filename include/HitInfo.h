#ifndef HITINFO
#define HITINFO

#include "ICollideable.h"

struct HitInfo
{
    HitInfo(){mHitObject=nullptr;mIntersectionPoint=sf::Vector2f(0.f, 0.f);mDistanceAway=0.f;}
    HitInfo(ICollideable* obj, sf::Vector2f point, float dist){mHitObject=obj;mIntersectionPoint=point;mDistanceAway=dist;}
    ~HitInfo(){delete mHitObject;}

    ICollideable* mHitObject;
    sf::Vector2f mIntersectionPoint;
    float mDistanceAway;
};

#endif
