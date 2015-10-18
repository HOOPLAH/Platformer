#ifndef FUNCUTILS_H_INCLUDED
#define FUNCUTILS_H_INCLUDED

#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "SpriteInfo.h"

float length(sf::Vector2f a);
void rotateVec(sf::Vector2f& v, float degrees, const sf::Vector2f& center=sf::Vector2f());

std::vector<std::string> splitStringBySpaces(std::string line);

#endif // FUNCUTILS_H_INCLUDED
