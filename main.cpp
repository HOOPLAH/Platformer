#include <SFML/Graphics.hpp>

#define USE_PATHER

#include <cstdlib>
#include <ctime>
#include <stdarg.h>
#include <iostream>

#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>
#include <sqrat.h>

#include "Assets.h"
#include "WorldManager.h"
#include "Constants.h"

#include "Item.h"
#include "Inventory.h"
#include "Player.h"

void sqprintfunc(HSQUIRRELVM v, const SQChar *s, ...)
{
    va_list arglist;
    va_start(arglist, s);
    vprintf((char*)s, arglist);
    va_end(arglist);
}

void bindSquirrel(HSQUIRRELVM vm)
{
    Sqrat::Class<Item> itemClass(vm, "Item");
    itemClass.Func("setStackSize", &Item::setStackSize);
    itemClass.Func("setName", &Item::setName);
    itemClass.Func("getCount", &Item::getCount);
    itemClass.Func("getName", &Item::getName);
    itemClass.Func("use", &Item::use);
    Sqrat::RootTable().Bind("Item", itemClass);

    Sqrat::Class<Inventory> inventoryClass(vm, "Inventory");
    inventoryClass.Func("push_back", &Inventory::sq_push_back);
    inventoryClass.Func("getItem", &Inventory::getItem);
    Sqrat::RootTable().Bind("Inventory", inventoryClass);

    Sqrat::Class<Player> playerClass(vm, "Player");
    playerClass.Func("getInventory", &Player::getInventory);
    Sqrat::RootTable().Bind("Player", playerClass);
}

int main()
{
    srand((unsigned)time(0));

    Assets::loadAssets();

    HSQUIRRELVM vm = sq_open(1064);

    sq_setprintfunc(vm, sqprintfunc, NULL);
    Sqrat::ErrorHandling::Enable(true);
    sq_pushroottable(vm);
    sqstd_register_iolib(vm);
    sqstd_seterrorhandlers(vm);

    Sqrat::Script script(vm);
    Sqrat::DefaultVM::Set(vm);
    bindSquirrel(vm);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Platformer");

    WorldManager worldMgr(vm);

    std::string error;
    if (!script.CompileFile("script.nut", error) || !script.Run(error))
    {
        std::cout << "Squirrel Error: " << error << std::endl;
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

                worldMgr.handleEvents(event);
            }

            worldMgr.update(ticks);
            accumulator -= UPDATE_STEP;

            ticks++;
		}

		float alpha = accumulator.asSeconds()/UPDATE_STEP.asSeconds();

        window.clear();
        worldMgr.draw(window, alpha);
        window.display();
    }

    window.close();

    Sqrat::RootTable().Release();
    script.Release();
    sq_close(vm);

    return 0;
}
