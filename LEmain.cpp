#include <SFML/Graphics.hpp>

#define USE_PATHER

#include <cstdlib>
#include <ctime>

#include "Assets.h"
#include "LevelEditor.h"
#include "Constants.h"

int main()
{
    srand((unsigned)time(0));

    Assets::loadAssets();

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer");

    LevelEditor levelEditor;

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
                if (event.type == sf::Event::Closed)
                    window.close();

                levelEditor.handleEvents(event);
            }

            levelEditor.update(ticks);
            accumulator -= UPDATE_STEP;

            ticks++;
		}

		float alpha = accumulator.asSeconds()/UPDATE_STEP.asSeconds();

        window.clear();
        levelEditor.draw(window, alpha);
        window.display();
    }

    window.close();

    return 0;
}
