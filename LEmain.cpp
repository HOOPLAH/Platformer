#include <SFML/Graphics.hpp>

#define USE_PATHER

#include <cstdlib>
#include <ctime>

#include "Assets.h"
#include "WorldEditor.h"
#include "Constants.h"

int main()
{
    srand((unsigned)time(0));

    Assets::loadAssets();

    HSQUIRRELVM vm = sq_open(1064);
    sq_setprintfunc(vm, sqprintfunc, NULL);
    Sqrat::Script *script = new Sqrat::Script(vm);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer");

    WorldEditor worldEditor("Content/Worlds/test2.txt", vm);

    //Sqrat::RootTable(vm).Func("getInputString", sqgetinputstring);
    //Sqrat::RootTable(vm).Func("getInputNumber", sqgetinputnumber);

    //Game::bindSquirrel(script->GetVM());

    std::string error;
    if (!script->CompileFile("script.nut", error))
    {
        std::cout << "Squirrel Error: " << error << std::endl;
    }
    else
    {
        if (!script->Run(error))
        {
            std::cout << "Squirrel Error: " << error << std::endl;
        }
    }

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

                worldEditor.handleEvents(event);
            }

            worldEditor.update(ticks);
            accumulator -= UPDATE_STEP;

            ticks++;
		}

		float alpha = accumulator.asSeconds()/UPDATE_STEP.asSeconds();

        window.clear();
        worldEditor.draw(window, alpha);
        window.display();
    }

    window.close();

    return 0;
}
