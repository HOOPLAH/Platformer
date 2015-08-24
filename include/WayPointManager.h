#ifndef WAYPOINTMANAGER_H
#define WAYPOINTMANAGER_H

#include <vector>

#include <SFML/Graphics.hpp>
#include "micropather.h"

#include "WayPoint.h"

class WayPointManager : public micropather::Graph
{
    public:
        WayPointManager();
        ~WayPointManager();

        void draw(sf::RenderTarget& target);

        void addWayPoint(WayPoint pt){mWayPoints.push_back(pt);}
        void addWayPointEdge(int startIndex, int endIndex, int type);

        std::vector<WayPoint>& getWayPoints(){return mWayPoints;}
        int getNextWayPointIndex(){return mWayPoints.size();}

        float LeastCostEstimate(void* stateStart, void* stateEnd);
		void AdjacentCost(void* state, std::vector<micropather::StateCost>* adjacent);
		void getPath(std::vector<WayPoint*>& path, int index, int targetIndex);
		void PrintStateInfo(void* state){}

    private:
        std::vector<WayPoint> mWayPoints;

        micropather::MicroPather* mPather;
};

#endif // WAYPOINTMANAGER_H
