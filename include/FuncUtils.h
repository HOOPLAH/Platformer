#ifndef FUNCUTILS_H_INCLUDED
#define FUNCUTILS_H_INCLUDED

#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>

float length(sf::Vector2f a);
void rotateBy(sf::Vector2f& v, float degrees, const sf::Vector2f& center=sf::Vector2f());

std::vector<std::string> splitStringBySpaces(std::string line);

#endif // FUNCUTILS_H_INCLUDED
