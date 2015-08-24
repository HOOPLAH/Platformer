#include "VecUtils.h"

#include <cmath>

float length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}
