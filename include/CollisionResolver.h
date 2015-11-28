#ifndef COLLISIONRESOLVER_H
#define COLLISIONRESOLVER_H

#include <vector>
#include <memory>

#include "ICollideable.h"
#include "QuadTree.h"

class CollisionResolver
{
    public:
        CollisionResolver(QuadTree& quad);
        ~CollisionResolver();

        void update(std::vector<std::shared_ptr<ICollideable>>& collideables);

    private:
        bool check(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);
        void resolve(std::weak_ptr<ICollideable> a, std::weak_ptr<ICollideable> b);

        QuadTree& mQuadTree;
};

#endif // COLLISIONRESOLVER_H
