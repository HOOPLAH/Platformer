#include "FuncUtils.h"

#include <cmath>
#include <sstream>

float length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
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
