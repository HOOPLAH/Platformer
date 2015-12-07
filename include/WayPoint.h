#ifndef WAYPOINT_H_INCLUDED
#define WAYPOINT_H_INCLUDED

#include "SFML/System/Vector2.hpp"

#include <iostream>

namespace WayPointType
{
    enum
    {
        WALK = 0,
        JUMP = 1,
        STOP = 2
    };
}

struct WayPointEdge
{
    WayPointEdge(){}
    WayPointEdge(std::size_t index, int type) : mTargetIndex(index), mType(type) {}

    std::size_t mTargetIndex;
    int mType;
};

struct WayPoint
{
    WayPoint(){}
    WayPoint(float x, float y, std::size_t index) :
        mPosition(sf::Vector2f(x, y)),
        mIndex(index)
        {}
    WayPoint(sf::Vector2f pos, std::size_t index) :
        mPosition(pos),
        mIndex(index)
        {}

    WayPointEdge* getEdge(std::size_t targetWayPtIndex)
    {
        for (auto& edge : mEdges)
        {
            if (edge.mTargetIndex == targetWayPtIndex)
            {
                return &edge;
            }
        }

        return nullptr;
    }

    sf::Vector2f mPosition;
    std::size_t mIndex;
    std::vector<WayPointEdge> mEdges;
};

#endif // WAYPOINT_H_INCLUDED
