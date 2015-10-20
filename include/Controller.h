#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Window/Event.hpp>

#include "ICollideable.h"

class Controller
{
    public:
        Controller(ICollideable& obj);
        virtual ~Controller();

        virtual void handleEvents(sf::Event& event){}

    protected:
        ICollideable& mObject;
};

#endif // CONTROLLER_H
