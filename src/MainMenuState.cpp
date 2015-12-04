#include "MainMenuState.h"

#include "Constants.h"
#include "GameState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace),
    mPlayButton(Assets::sprites["playbutton"], sf::Vector2f())
{
    mBackGround = sf::Sprite(Assets::sprites["background"].mTexture);
    mPlayButton.setRenderPosition(sf::Vector2f(SCREEN_WIDTH/2 - (mPlayButton.getSpriteInfo().mFrameDim.x/2), SCREEN_HEIGHT/2 - (mPlayButton.getSpriteInfo().mFrameDim.y/2)));
}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update(int ticks)
{
    if (mPlayButton.isPressed())
        mNext = StateMachine::build<GameState>(mMachine, true);

    mPlayButton.update();
}

void MainMenuState::draw(sf::RenderTarget& target, float alpha)
{
    target.draw(mBackGround);

    mPlayButton.draw(target, alpha);
}

void MainMenuState::handleEvents(sf::Event& event)
{
    mPlayButton.handleEvents(event);
}
