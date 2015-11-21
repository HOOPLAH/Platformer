#ifndef COLLISIONRESOLVER_H
#define COLLISIONRESOLVER_H

#include <vector>
#include <memory>

#include "ICollideable.h"

class CollisionResolver
{
    public:
        CollisionResolver();
        ~CollisionResolver();

        void update();

        std::vector<std::shared_ptr<ICollideable>>& getCollideables(){return mCollideables;}

    private:
        bool check(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
        void resolve(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);

        std::vector<std::shared_ptr<ICollideable>> mCollideables;
};

#endif // COLLISIONRESOLVER_H
