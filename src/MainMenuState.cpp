#include "MainMenuState.h"

#include "Constants.h"
#include "GameState.h"
#include "MainSettingsState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace),
    mPlayButton(Assets::sprites["plainbutton"], sf::Vector2f(), "Play"),
    mSettingsButton(Assets::sprites["plainbutton"], sf::Vector2f(), "Settings"),
    mQuitButton(Assets::sprites["plainbutton"], sf::Vector2f(), "Quit")
{
    mPlayButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mPlayButton.getSpriteInfo().mFrameDim.x/2), 150 - (mPlayButton.getSpriteInfo().mFrameDim.y/2)));
    mSettingsButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mSettingsButton.getSpriteInfo().mFrameDim.x/2), 250 - (mSettingsButton.getSpriteInfo().mFrameDim.y/2)));
    mQuitButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mQuitButton.getSpriteInfo().mFrameDim.x/2), 350 - (mQuitButton.getSpriteInfo().mFrameDim.y/2)));
    mBackGround = sf::Sprite(Assets::sprites["nightbackground"].mTexture);
}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update(int ticks)
{
    if (mPlayButton.isPressed())
    {
        mNext = StateMachine::build<GameState>(mMachine, true);
    }
    else if (mSettingsButton.isPressed())
    {
        mNext = StateMachine::build<MainSettingsState>(mMachine, true);
    }
    else if (mQuitButton.isPressed())
    {
        mMachine.quit();
    }

    mPlayButton.update();
    mSettingsButton.update();
    mQuitButton.update();
}

void MainMenuState::draw(sf::RenderTarget& target, float alpha)
{
    target.draw(mBackGround);

    mPlayButton.draw(target, alpha);
    mSettingsButton.draw(target, alpha);
    mQuitButton.draw(target, alpha);
}

void MainMenuState::handleEvents(sf::Event& event)
{
    mPlayButton.handleEvents(event);
    mSettingsButton.handleEvents(event);
    mQuitButton.handleEvents(event);
}
