#include "CollisionResolver.h"

#include <iostream>

CollisionResolver::CollisionResolver(QuadTree& quad) :
    mQuadTree(quad)
{
    //ctor
}

CollisionResolver::~CollisionResolver()
{
    //dtor
}

void CollisionResolver::update(std::vector<std::shared_ptr<ICollideable>>& collideables)
{
    for (auto& obj : collideables)
    {
        auto returnObjects = mQuadTree.getObjectsAt(obj->getPhysicsPosition());
        for (auto& colObj : returnObjects)
        {
            auto bigger = obj;
            auto smaller = colObj.lock();

            // check which object is bigger

            if ((obj->getHitBox().width*obj->getHitBox().height) > (colObj.lock()->getHitBox().width*colObj.lock()->getHitBox().height))
            {
                bigger = obj;
                smaller = colObj.lock();
            }
            else if ((obj->getHitBox().width*obj->getHitBox().height) < (colObj.lock()->getHitBox().width*colObj.lock()->getHitBox().height))
            {
                smaller = obj;
                bigger = colObj.lock();
            }

            // check if one of the objects is static - static objects always win

            if (obj->isStatic())
            {
                bigger = obj;
                smaller = colObj.lock();
            }
            else if (colObj.lock()->isStatic())
            {
                smaller = obj;
                bigger = colObj.lock();
            }

            // now check for collisions

            if (bigger != smaller && !(bigger->isStatic() && smaller->isStatic()))
            {
                if (check(smaller, bigger) && bigger->isCollisionActive() && smaller->isCollisionActive())
                    resolve(smaller, bigger);
            }
        }
    }

    // check collisions
    /*for (std::size_t x = 0; x < collideables.size(); x++)
    {
        for (std::size_t y = x+1; y < collideables.size(); y++)
        {
            auto dynamic = collideables[x];
            auto _static = collideables[y];

            if (!collideables[x]->isStatic())
                dynamic = collideables[x];
            else if (!collideables[y]->isStatic())
                dynamic = collideables[y];

            if (collideables[x]->isStatic())
                _static = collideables[x];
            else if (collideables[y]->isStatic())
                _static = collideables[y];

            if (check(dynamic, _static) && dynamic->isCollisionActive() && _static->isCollisionActive())
                resolve(dynamic, _static);
        }
    }*/
}

bool CollisionResolver::check(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
    sf::Vector2f a1 = a.lock()->getPhysicsPosition() + sf::Vector2f(a.lock()->getHitBox().left, a.lock()->getHitBox().top);
    sf::Vector2f a2 = sf::Vector2f(a.lock()->getHitBox().width, a.lock()->getHitBox().height);

    sf::Vector2f b1 = b.lock()->getPhysicsPosition() + sf::Vector2f(b.lock()->getHitBox().left, b.lock()->getHitBox().top);
    sf::Vector2f b2 = sf::Vector2f(b.lock()->getHitBox().width, b.lock()->getHitBox().height);

    //float rect = (left, top, width, height)
    sf::FloatRect aRect(a1, a2);
    sf::FloatRect bRect(b1, b2);

    if (aRect.intersects(bRect))
        return true;

    return false;
}

void CollisionResolver::resolve(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b)
{
    auto aLeft = a.lock()->getPhysicsPosition().x + a.lock()->getHitBox().left;
    auto aTop = a.lock()->getPhysicsPosition().y + a.lock()->getHitBox().top;
    auto aRight = aLeft + a.lock()->getHitBox().width;
    auto aBottom = aTop + a.lock()->getHitBox().height;

    auto bLeft = b.lock()->getPhysicsPosition().x + b.lock()->getHitBox().left;
    auto bTop = b.lock()->getPhysicsPosition().y + b.lock()->getHitBox().top;
    auto bRight = bLeft + b.lock()->getHitBox().width;
    auto bBottom = bTop + b.lock()->getHitBox().height;

    float overlapLeft {aRight - bLeft};
    float overlapRight {bRight - aLeft};
    float overlapTop {aBottom - bTop};
    float overlapBottom {bBottom - aTop};

    bool fromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool fromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX {fromLeft ? overlapLeft : overlapRight};
    float minOverlapY {fromTop ? overlapTop : overlapBottom};

    auto y_collision = [a, fromTop](float overlapX, float overlapY, bool stair=false)
    {
        if (fromTop)
        {
            if (stair)
            {
                a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
                a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x-5.f, a.lock()->getPhysicsPosition().y - overlapY));
            }
            else
            {
                a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
                a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y - overlapY));
            }
        }
        else if (!fromTop)
        {
            a.lock()->setVelocity(sf::Vector2f(a.lock()->getVelocity().x, 0.f));
            a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x, a.lock()->getPhysicsPosition().y + overlapY));
        }
    };

    auto x_collision = [a, fromLeft, fromTop, y_collision](float overlapX, float overlapY)
    {
        if (overlapY < 20.f && fromTop) // it's probably a stair
        {
            y_collision(overlapX, overlapY, true);
            return;
        }

        a.lock()->setVelocity(sf::Vector2f(0.f, a.lock()->getVelocity().y));

        if (fromLeft)
        {
            a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x - overlapX, a.lock()->getPhysicsPosition().y));
        }
        else if (!fromLeft)
        {
            a.lock()->setPhysicsPosition(sf::Vector2f(a.lock()->getPhysicsPosition().x + overlapX, a.lock()->getPhysicsPosition().y));
        }
    };

    if (a.lock()->onContactBegin(b, fromLeft, fromTop) && b.lock()->onContactBegin(a, fromLeft, fromTop))
    {
        if (std::abs(minOverlapX) > std::abs(minOverlapY)) // y overlap
        {
            y_collision(minOverlapX, minOverlapY);
        }
        else if (std::abs(minOverlapX) < std::abs(minOverlapY)) // x overlap
        {
            x_collision(minOverlapX, minOverlapY);
        }

        a.lock()->onContactEnd(b);
        b.lock()->onContactEnd(a);
    }
}
