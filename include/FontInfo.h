#ifndef FONTINFO_H_INCLUDED
#define FONTINFO_H_INCLUDED

#include <SFML/Graphics/Font.hpp>

struct FontInfo
{
    FontInfo() {}
    FontInfo(std::string path)
    {
        mFont.loadFromFile(path);
    }

    sf::Font mFont;
};

#endif // FONTINFO_H_INCLUDED
