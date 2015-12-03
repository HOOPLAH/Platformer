#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <memory>

#include <SFML/Graphics/Rect.hpp>

#include "ICollideable.h"

class QuadTree
{
    public:
        QuadTree(sf::IntRect rect, int level, int maxLevel);
        ~QuadTree();

        void addObject(std::weak_ptr<ICollideable> obj);
        std::vector<std::weak_ptr<ICollideable>> getObjectsAt(sf::Vector2f pos);
        void clear();

        sf::IntRect& getIntRect(){return mRect;}
        void setIntRect(sf::IntRect rect){mRect=rect;}

    private:
        sf::IntRect mRect;
        std::size_t	mLevel;
        std::size_t mMaxLevel;
        std::vector<std::weak_ptr<ICollideable>> mObjects;

        std::unique_ptr<QuadTree> mParent;
        std::unique_ptr<QuadTree> NW;
        std::unique_ptr<QuadTree> NE;
        std::unique_ptr<QuadTree> SW;
        std::unique_ptr<QuadTree> SE;

        bool contains(QuadTree& child, std::weak_ptr<ICollideable> obj);
};

#endif // QUADTREE_H
