#include "Line.h"

#include "Constants.h"

#include <iostream>

Line::Line(sf::Vector2f point_a, sf::Vector2f point_b, sf::Color color)
{
    mVertices = sf::VertexArray(sf::Lines, 2);
    mVertices[0].position = point_a;
    mVertices[1].position = point_b;

    mVertices[0].color = color;
    mVertices[1].color = color;
}

Line::~Line()
{
    mVertices.clear();
}

void Line::draw(sf::RenderTarget& target)
{
    target.draw(mVertices);
}

void Line::move(sf::Vector2f offset)
{
    setStart(getStart() + offset);
    setEnd(getEnd() + offset);
}

void Line::rotate(float degrees)
{
    auto rotateVector = [](sf::Vector2f v, float degrees, const sf::Vector2f& midpoint=sf::Vector2f()) -> sf::Vector2f
    {
        float theta = degrees*DEGTORAD;
        float x_new = (  (v.x - midpoint.x) * cos(theta) + (v.y - midpoint.y) * sin(theta) ) + midpoint.x;
        float y_new = ( -(v.x - midpoint.x) * sin(theta) + (v.y - midpoint.y) * cos(theta) ) + midpoint.y;
        return sf::Vector2f(x_new, y_new);
    };

    sf::Vector2f midpoint = sf::Vector2f((getStart().x+getEnd().x)/2, (getStart().y+getEnd().y)/2);
    rotateVector(getStart(), degrees, midpoint);
    rotateVector(getEnd(), degrees, midpoint);
}

/*Vector2<T>& rotateBy(float degrees, const Vector2<T>& center=Vector2<T>())
{
    degrees *= 3.14159f/180.f;
    const float cs = cos(degrees);
    const float sn = sin(degrees);

    x -= center.x;
    y -= center.y;

    T nx = (T)(x*cs - y*sn);
    T ny = (T)(x*sn + y*cs);

    x = nx;
    y = ny;

    x += center.x;
    y += center.y;
    return *this;
}*/
