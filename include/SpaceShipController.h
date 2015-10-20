#ifndef SPACESHIPCONTROLLER_H
#define SPACESHIPCONTROLLER_H

#include "Controller.h"

class SpaceShipController : public Controller
{
    public:
        SpaceShipController(ICollideable& obj);
        ~SpaceShipController();

    private:
};

#endif // SPACESHIPCONTROLLER_H
