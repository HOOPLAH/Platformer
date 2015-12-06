#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <vector>
#include <memory>

#include "IState.h"
#include "Button.h"

class MainMenuState : public IState
{
    public:
        MainMenuState(StateMachine& stateMachine, bool replace = true, bool dayTime = false);
        ~MainMenuState();

        void pause(){}
        void resume(){}

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

    private:
        sf::Vector2f mMousePosition;
        Button mPlayButton;
        Button mSettingsButton;
        Button mQuitButton;
        sf::Sprite mBackGround;
        bool mDayTime;
        std::vector<std::unique_ptr<IRenderable>> mRenderables;
};

#endif // MAINMENUSTATE_H
