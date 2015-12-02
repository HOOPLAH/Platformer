#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#define USE_PATHER

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Assets.h"
#include "Constants.h"
#include "MainMenuState.h"
#include "StateMachine.h"

int main()
{
    srand((unsigned)time(0));

    Assets::loadAssets();

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer");

    ImGui::SFML::SetWindow(window);
	ImGui::SFML::InitImGui();

	StateMachine statesMachine;
	statesMachine.run(StateMachine::build<MainMenuState>(statesMachine, true));

    sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	int ticks = 0;
    while (window.isOpen())
    {
        //update logic
        sf::Time dt = clock.restart();
		accumulator += dt;
		while (accumulator > UPDATE_STEP)
		{
            sf::Event event;
            while (window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed)
                    window.close();

                statesMachine.handleEvents(event);
            }

            statesMachine.nextState();
            statesMachine.update(ticks);
            accumulator -= UPDATE_STEP;

            ticks++;
		}

		float alpha = accumulator.asSeconds()/UPDATE_STEP.asSeconds();

        window.clear();

        ImGui::SFML::UpdateImGui();

		statesMachine.draw(window, alpha);

		ImGui::End();
        ImGui::Render();

        window.display();
    }

    window.close();

    return 0;
}
