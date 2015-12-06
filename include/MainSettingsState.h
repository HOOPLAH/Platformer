#ifndef MAINSETTINGSSTATE_H
#define MAINSETTINGSSTATE_H

#include "IState.h"
#include "Button.h"

class MainSettingsState : public IState
{
    public:
        MainSettingsState(StateMachine& stateMachine, bool replace = true);
        ~MainSettingsState();

        void pause(){}
        void resume(){}

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

    private:
        sf::Sprite mBackGround;
        Button mBackButton;
};

#endif // MAINSETTINGSSTATE_H
