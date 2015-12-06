#include "GameState.h"

#include "StateMachine.h"

GameState::GameState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace),
    mPaused(false)
{
    //ctor
}

GameState::~GameState()
{
    //dtor
}

void GameState::pause()
{
    mPaused = true;

    mWorldManager.getCurrentWorld().getHero().lock()->getSprite().setColor(sf::Color(109, 109, 109));
    for (auto& obj : mWorldManager.getCurrentWorld().getRenderables())
    {
        obj->getSprite().setColor(sf::Color(109, 109, 109));
    }
}

void GameState::resume()
{
    mPaused = false;

    mWorldManager.getCurrentWorld().getHero().lock()->stop();
    mWorldManager.getCurrentWorld().getHero().lock()->getSprite().setColor(sf::Color(255, 255, 255));

    for (auto& obj : mWorldManager.getCurrentWorld().getRenderables())
    {
        obj->getSprite().setColor(sf::Color(255, 255, 255));
    }
}

void GameState::update(int ticks)
{
    if (!mPaused)
        mWorldManager.update(ticks);
}

void GameState::draw(sf::RenderTarget& target, float alpha)
{
    mWorldManager.draw(target, alpha);

    if (mPaused)
    {
        sf::Text text("Paused", Assets::fonts["8bit"].mFont, 14);
        text.setPosition((SCREEN_WIDTH/2) - text.getGlobalBounds().width/2, (SCREEN_HEIGHT/2) - text.getGlobalBounds().height/2);
        target.draw(text);
    }
}

void GameState::handleEvents(sf::Event& event)
{
    if (!mPaused)
        mWorldManager.handleEvents(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            mPaused = !mPaused;

            if (mPaused)
                pause();
            else
                resume();
        }
    }
}
