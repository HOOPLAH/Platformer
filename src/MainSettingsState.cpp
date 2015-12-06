#include "MainSettingsState.h"

#include "Assets.h"
#include "Constants.h"
#include "MainMenuState.h"
#include "StateMachine.h"

MainSettingsState::MainSettingsState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace),
    mBackGround(Assets::sprites["nightbackground"].mTexture),
    mBackButton(Assets::sprites["plainbutton"], sf::Vector2f(), "Back")
{
    mBackButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2-mBackButton.getSpriteInfo().mFrameDim.x/2, 350-mBackButton.getSpriteInfo().mFrameDim.y/2));
}

MainSettingsState::~MainSettingsState()
{
    //dtor
}

void MainSettingsState::update(int ticks)
{
    mBackButton.update();

    if (mBackButton.isPressed())
    {
        mNext = StateMachine::build<MainMenuState>(mMachine, true);
    }
}

void MainSettingsState::draw(sf::RenderTarget& target, float alpha)
{
    target.draw(mBackGround);

    mBackButton.draw(target, alpha);
}

void MainSettingsState::handleEvents(sf::Event& event)
{
    mBackButton.handleEvents(event);
}
