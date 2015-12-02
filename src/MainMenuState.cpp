#include "MainMenuState.h"

#include "imgui.h"

#include "GameState.h"
#include "StateMachine.h"

MainMenuState::MainMenuState(StateMachine& stateMachine, bool replace) : IState(stateMachine, replace)
{
    //ctor
}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update(int ticks)
{

}

void MainMenuState::draw(sf::RenderTarget& target, float alpha)
{
    static bool ui = true;
    if (ImGui::Begin("Test!", &ui, ImVec2(10, 10)))
    {
        if (ImGui::Button("Play", ImVec2(96, 32)))
        {
            mNext = StateMachine::build<GameState>(mMachine, true);
        }
    }
}

void MainMenuState::handleEvents(sf::Event& event)
{

}
