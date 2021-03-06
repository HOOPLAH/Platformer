#include "Assets.h"

std::map<std::string, SpriteInfo> Assets::sprites;
std::map<std::string, FontInfo> Assets::fonts;

void Assets::loadAssets()
{
    sprites["nothing"] = SpriteInfo("Content/Textures/nothing.png");
    sprites["ammocrate"] = SpriteInfo("Content/Textures/ammocrate.png");
    sprites["ammocrate2"] = SpriteInfo("Content/Textures/ammocrate2.png");
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
    sprites["grassblock"] = SpriteInfo("Content/Textures/grass_block.png");
    sprites["tilegrassblock"] = SpriteInfo("Content/Textures/grass_block_tileable.png");
    sprites["rockbottom"] = SpriteInfo("Content/Textures/rock_bottom.png");
    sprites["tallrock"] = SpriteInfo("Content/Textures/tall_rock.png");
    sprites["daybackground"] = SpriteInfo("Content/Textures/nosun-daybackground.png");
    sprites["nightbackground"] = SpriteInfo("Content/Textures/nightbackground.png");
    sprites["cloud"] = SpriteInfo("Content/Textures/cloud.png");
    sprites["mountain"] = SpriteInfo("Content/Textures/mountain_background.png");
    sprites["sign"] = SpriteInfo("Content/Textures/sign.png");
    sprites["plainbutton"] = SpriteInfo("Content/Textures/plainbutton.png", 3, 1);
    sprites["ladder"] = SpriteInfo("Content/Textures/ladder.png");
    sprites["tree"] = SpriteInfo("Content/Textures/tree.png");
    sprites["leaves"] = SpriteInfo("Content/Textures/leaves.png");

    sprites["tree"].mHitBox = sf::FloatRect(0, 58, 256, 17);
    sprites["grenade"] = SpriteInfo("Content/Textures/grenade.png");
    sprites["grenade"].mHitBox = sf::FloatRect(1.f, 4.f, 4.f, 4.f);
    sprites["bluepeewee"] = SpriteInfo("Content/Textures/bluepeewee.png", 36, 6);
    sprites["bluepeewee"].mHitBox = sf::FloatRect(20.f, 10.f, 24.f, 44.f);
    sprites["pinkpeewee"] = SpriteInfo("Content/Textures/pinkpeewee.png", 36, 6);
    sprites["pinkpeewee"].mHitBox = sf::FloatRect(20.f, 10.f, 24.f, 44.f);
    sprites["bigplatform"] = SpriteInfo("Content/Textures/bigplatform.png");
    sprites["bigplatform"].mHitBox = sf::FloatRect(10.f, 12.f, 225.f, 124.f);
    sprites["smallplatform"] = SpriteInfo("Content/Textures/smallplatform.png");
    sprites["smallplatform"].mHitBox = sf::FloatRect(5.f, 8.f, 35.f, 26.f);
    sprites["bridge"] = SpriteInfo("Content/Textures/bridge.png");
    sprites["bridge"].mHitBox = sf::FloatRect(6.f, 37.f, 140.f, 6.f);
    sprites["commandcenter"] = SpriteInfo("Content/Textures/command_center.png");
    //sprites["commandcenter"].mHitBox = sf::FloatRect(56.f, 86.f, 40.f, 20.f);

    ///

    fonts["8bit"] = FontInfo("Content/Fonts/8bit.ttf");
}
