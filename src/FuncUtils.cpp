#include "FuncUtils.h"

#include <cmath>
#include <sstream>

#include "Constants.h"

float length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

void rotateVec(sf::Vector2f& v, float degrees, const sf::Vector2f& center)
{
    degrees *= DEGTORAD;
    const float cs = cos(degrees);
    const float sn = sin(degrees);

    v.x -= center.x;
    v.y -= center.y;

    float nx = (float)(v.x*cs - v.y*sn);
    float ny = (float)(v.x*sn + v.y*cs);

    v.x = nx;
    v.y = ny;

    v.x += center.x;
    v.y += center.y;
}

std::vector<std::string> splitStringBySpaces(std::string line)
{
    std::istringstream iss(line);
    std::vector<std::string> split_array;
    while (iss)
    {
        std::string sub;
        iss >> sub;
        split_array.push_back(sub);
    }

    return split_array;
}
