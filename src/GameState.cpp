#include "GameState.h"

#include "imgui.h"

GameState::GameState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace)
{
    //ctor
}

GameState::~GameState()
{
    //dtor
}

void GameState::update(int ticks)
{
    mWorldManager.update(ticks);
}

void GameState::draw(sf::RenderTarget& target, float alpha)
{
    mWorldManager.draw(target, alpha);

    static bool ui = true;
    ImGui::Begin("Test!", &ui, ImVec2(0, 0));
}

void GameState::handleEvents(sf::Event& event)
{
    mWorldManager.handleEvents(event);
}
