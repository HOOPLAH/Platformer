#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "IState.h"

class MainMenuState : public IState
{
    public:
        MainMenuState(StateMachine& stateMachine, bool replace = true);
        ~MainMenuState();

        void pause(){}
        void resume(){}

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

    private:
};

#endif // MAINMENUSTATE_H
