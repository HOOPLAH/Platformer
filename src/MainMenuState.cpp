#include "MainMenuState.h"

#include "imgui.h"

#include "GameState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace),
    mPlayButton(Assets::sprites["playbutton"], sf::Vector2f())
{
    mBackGround = sf::Sprite(Assets::sprites["background"].mTexture);
}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update(int ticks)
{
    if (mPlayButton.isPressed())
        mNext = StateMachine::build<GameState>(mMachine, true);

    if (sf::FloatRect(mPlayButton.getRenderPosition(), mPlayButton.getSpriteInfo().mFrameDim).contains(mMousePosition))
    {
        //mPlayButton.setState(ButtonStates::Hover);
    }
    else
    {
        //mPlayButton.setState(ButtonStates::Up);
    }
}

void MainMenuState::draw(sf::RenderTarget& target, float alpha)
{
    target.draw(mBackGround);

    mPlayButton.draw(target, alpha);
}

void MainMenuState::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        mMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (sf::FloatRect(mPlayButton.getRenderPosition(), mPlayButton.getSpriteInfo().mFrameDim).contains(mMousePosition))
            {
                mPlayButton.setPressed(true);
                mPlayButton.setState(ButtonStates::Down);
            }
        }
    }
}
