#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "IState.h"
#include "WorldManager.h"

class GameState : public virtual IState
{
    public:
        GameState(StateMachine& stateMachine, bool replace = true);
        ~GameState();

        void pause(){}
        void resume(){}

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

    private:
        WorldManager mWorldManager;
};

#endif // GAMESTATE_H
