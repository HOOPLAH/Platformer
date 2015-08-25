#include "Assets.h"

std::map<std::string, SpriteInfo> Assets::sprites;
std::map<std::string, FontInfo> Assets::fonts;

void Assets::loadAssets()
{
    sprites["ammocrate"] = SpriteInfo("Content/Textures/ammocrate.png");
    sprites["play_button"] = SpriteInfo("Content/Textures/play_button.png");
    sprites["pistol"] = SpriteInfo("Content/Textures/pistol.png");
    sprites["bullet"] = SpriteInfo("Content/Textures/bullet.png");

    sprites["kingkam"] = SpriteInfo("Content/Textures/kingkam.png", 12, 6);

    sprites["bluepeewee"] = SpriteInfo("Content/Textures/bluepeewee.png", 36, 6);
        sprites["bluepeewee"].mHitBox = sf::FloatRect(20.f, 10.f, 24.f, 44.f);
    sprites["pinkpeewee"] = SpriteInfo("Content/Textures/pinkpeewee.png", 36, 6);
        sprites["pinkpeewee"].mHitBox = sf::FloatRect(20.f, 10.f, 24.f, 44.f);
    sprites["bigplatform"] = SpriteInfo("Content/Textures/bigplatform.png");
        sprites["bigplatform"].mHitBox = sf::FloatRect(10.f, 12.f, 225.f, 124.f);
    sprites["smallplatform"] = SpriteInfo("Content/Textures/smallplatform.png");
        sprites["smallplatform"].mHitBox = sf::FloatRect(5.f, 8.f, 35.f, 26.f);
    sprites["blueplatform"] = SpriteInfo("Content/Textures/blueplatform.png");

    ///

    fonts["8bit"] = FontInfo("Content/Fonts/8bit.ttf");
}
