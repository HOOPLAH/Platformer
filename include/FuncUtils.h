#ifndef FUNCUTILS_H_INCLUDED
#define FUNCUTILS_H_INCLUDED

#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>

float length(sf::Vector2f a);

std::vector<std::string> splitStringBySpaces(std::string line);

#endif // FUNCUTILS_H_INCLUDED
