#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <SFML/System/Time.hpp>

const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

const float DEGTORAD = 3.14159f/180.f;
const float RADTODEG = 180.f/3.14159f;

const sf::Time UPDATE_STEP = sf::seconds(1.0f / 60.0f);

#endif // CONSTANTS_H_INCLUDED
