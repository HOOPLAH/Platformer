#include "QuadTree.h"

#include <algorithm>

QuadTree::QuadTree(sf::IntRect rect, int level, int maxLevel) :
	mRect(rect),
	mLevel(level),
	mMaxLevel(maxLevel)
{
	if (level == maxLevel)
		return;

	NW = std::make_unique<QuadTree>(sf::IntRect(rect.left, rect.top, rect.width/2.f, rect.height/2.f), level+1, maxLevel);
	NE = std::make_unique<QuadTree>(sf::IntRect(rect.left+rect.width/2.f, rect.top, rect.width/2.f, rect.height/2.f), level+1, maxLevel);

	SW = std::make_unique<QuadTree>(sf::IntRect(rect.left, rect.top+rect.height/2.f, rect.width/2.f, rect.height/2.f), level+1, maxLevel);
	SE = std::make_unique<QuadTree>(sf::IntRect(rect.left+rect.width/2.f, rect.top+rect.height/2.f, rect.width/2.f, rect.height/2.f), level+1, maxLevel);
}

QuadTree::~QuadTree()
{
    //dtor
}

void QuadTree::addObject(std::weak_ptr<ICollideable> obj)
{
    if (contains(*this, obj))
		mObjects.push_back(obj);

	if (mLevel == mMaxLevel)
		return;

	if (contains(*NW, obj))
	{
		NW->addObject(obj);
		return;
	}
	else if (contains(*NE, obj))
	{
		NE->addObject(obj);
		return;
	}
	else if (contains(*SW, obj))
	{
		SW->addObject(obj);
		return;
	}
	else if (contains(*SE, obj))
	{
		SE->addObject(obj);
		return;
	}
}

std::vector<std::weak_ptr<ICollideable>> QuadTree::getObjectsAt(sf::Vector2f pos)
{
	if (mLevel == mMaxLevel)
	{
		return mObjects;
	}

	std::vector<std::weak_ptr<ICollideable>> returnObjects;
	std::vector<std::weak_ptr<ICollideable>> childReturnObjects;
	if (!mObjects.empty())
	{
		returnObjects = mObjects;
	}
	if (pos.x > mRect.left+mRect.width/2.f && pos.x < mRect.left+mRect.width)
	{
		if (pos.y > mRect.top+mRect.height/2.f && pos.y < mRect.top+mRect.height)
		{
			childReturnObjects = SE->getObjectsAt(pos);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			//return returnObjects;
		}
		else if (pos.y > mRect.top && pos.y <= mRect.top+mRect.height/2.f)
		{
			childReturnObjects = NE->getObjectsAt(pos);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			//return returnObjects;
		}
	}
	else if (pos.x > mRect.left && pos.x <= mRect.left+mRect.width/2.f)
	{
		if (pos.y > mRect.top+mRect.height/2.f && pos.y < mRect.top+mRect.height)
		{
			childReturnObjects = SW->getObjectsAt(pos);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			//return returnObjects;
		}
		else if (pos.y > mRect.top && pos.y <= mRect.top+mRect.height/2.f)
		{
			childReturnObjects = NW->getObjectsAt(pos);
			returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
			//return returnObjects;
		}
	}

	return returnObjects;
}

void QuadTree::clear()
{
	if (mLevel == mMaxLevel)
	{
		mObjects.clear();
		return;
	}
	else
	{
		NW->clear();
		NE->clear();
		SW->clear();
		SE->clear();
		mObjects.clear();
	}
}

bool QuadTree::contains(QuadTree& child, std::weak_ptr<ICollideable> obj)
{
    sf::Vector2f a1 = obj.lock()->getPhysicsPosition() + sf::Vector2f(obj.lock()->getHitBox().left, obj.lock()->getHitBox().top);
    sf::Vector2f a2 = sf::Vector2f(obj.lock()->getHitBox().width, obj.lock()->getHitBox().height);
    sf::IntRect rect(a1.x, a1.y, a2.x, a2.y);
	return child.getIntRect().intersects(rect);
}
