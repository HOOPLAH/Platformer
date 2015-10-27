#include "Assets.h"

std::map<std::string, SpriteInfo> Assets::sprites;
std::map<std::string, FontInfo> Assets::fonts;

void Assets::loadAssets()
{
    sprites["nothing"] = SpriteInfo("Content/Textures/nothing.png");
    sprites["ammocrate"] = SpriteInfo("Content/Textures/ammocrate.png");
    sprites["ammocrate2"] = SpriteInfo("Content/Textures/ammocrate2.png");
    sprites["play_button"] = SpriteInfo("Content/Textures/play_button.png");
    sprites["pistol"] = SpriteInfo("Content/Textures/pistol.png");
    sprites["bullet"] = SpriteInfo("Content/Textures/bullet.png");
    sprites["turret"] = SpriteInfo("Content/Textures/turret.png");
    sprites["turrethead"] = SpriteInfo("Content/Textures/turrethead.png");
    sprites["turretbody"] = SpriteInfo("Content/Textures/turretbody.png");
    sprites["waypoint"] = SpriteInfo("Content/Textures/waypoint.png");
    sprites["blueplatform"] = SpriteInfo("Content/Textures/blueplatform.png");
    sprites["inventorybar"] = SpriteInfo("Content/Textures/inventorybar.png");
    sprites["curinventory"] = SpriteInfo("Content/Textures/curinventory.png");
    sprites["explosion"] = SpriteInfo("Content/Textures/explosion.png", 36, 6);
    sprites["ship"] = SpriteInfo("Content/Textures/ship.png", 2, 1);
    sprites["star"] = SpriteInfo("Content/Textures/star.png");

    sprites["grenade"] = SpriteInfo("Content/Textures/grenade.png");
    sprites["grenade"].mHitBox = sf::FloatRect(0.f, 5.f, 5.f, 5.f);
    sprites["bluepeewee"] = SpriteInfo("Content/Textures/bluepeewee.png", 36, 6);
    sprites["bluepeewee"].mHitBox = sf::FloatRect(20.f, 10.f, 24.f, 44.f);
    sprites["pinkpeewee"] = SpriteInfo("Content/Textures/pinkpeewee.png", 36, 6);
    sprites["pinkpeewee"].mHitBox = sf::FloatRect(20.f, 10.f, 24.f, 44.f);
    sprites["bigplatform"] = SpriteInfo("Content/Textures/bigplatform.png");
    sprites["bigplatform"].mHitBox = sf::FloatRect(10.f, 12.f, 225.f, 124.f);
    sprites["smallplatform"] = SpriteInfo("Content/Textures/smallplatform.png");
    sprites["smallplatform"].mHitBox = sf::FloatRect(5.f, 8.f, 35.f, 26.f);

    ///

    fonts["8bit"] = FontInfo("Content/Fonts/8bit.ttf");
}
