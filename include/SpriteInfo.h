#ifndef SPRITEINFO_H
#define SPRITEINFO_H

#include <SFML/Graphics.hpp>

struct SpriteInfo
{
    SpriteInfo() {}
    SpriteInfo(std::string path, int frames=1, int framesPerRow=1) :
        mFrames(frames),
        mFramesPerRow(framesPerRow)
    {
        mTexture.loadFromFile(path);
        mFrameDim = sf::Vector2f(mTexture.getSize().x/mFramesPerRow, mTexture.getSize().y/(mFrames/mFramesPerRow));
        mHitBox = sf::FloatRect(0.f, 0.f, mFrameDim.x, mFrameDim.y);
    }

    sf::Texture mTexture;
    int mFrames;
    int mFramesPerRow;
    sf::Vector2f mFrameDim;
    sf::FloatRect mHitBox;
};

#endif // SPRITEINFO_H
