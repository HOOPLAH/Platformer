#ifndef ASSETS_H
#define ASSETS_H

#include <map>

#include "SpriteInfo.h"
#include "FontInfo.h"

struct Assets
{
    static void loadAssets();
    static SpriteInfo& getSpriteInfo(std::string id);

    static std::map<std::string, SpriteInfo> sprites;
    static std::map<std::string, FontInfo> fonts;
};

#endif // ASSETS_H
