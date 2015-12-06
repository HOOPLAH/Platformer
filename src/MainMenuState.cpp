#include "MainMenuState.h"

#include "Constants.h"
#include "GameState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace),
    mPlayButton(Assets::sprites["playbutton"], sf::Vector2f()),
    mSettingsButton(Assets::sprites["plainbutton"], sf::Vector2f()),
    mQuitButton(Assets::sprites["plainbutton"], sf::Vector2f())
{
    mBackGround = sf::Sprite(Assets::sprites["background"].mTexture);
    mPlayButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mPlayButton.getSpriteInfo().mFrameDim.x/2), 150 - (mPlayButton.getSpriteInfo().mFrameDim.y/2)));
    mSettingsButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mPlayButton.getSpriteInfo().mFrameDim.x/2), 250 - (mPlayButton.getSpriteInfo().mFrameDim.y/2)));
    mQuitButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mPlayButton.getSpriteInfo().mFrameDim.x/2), 350 - (mPlayButton.getSpriteInfo().mFrameDim.y/2)));
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

    if (mQuitButton.isPressed())
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
