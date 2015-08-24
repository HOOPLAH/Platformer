#ifndef LINE
#define LINE

#include <SFML/Graphics.hpp>

class Line
{
    public:
        Line(sf::Vector2f point_a, sf::Vector2f point_b, sf::Color color);
        ~Line();

        void draw(sf::RenderTarget& target);

        sf::Vector2f getStart(){return mVertices[0].position;}
        sf::Vector2f getEnd(){return mVertices[1].position;}

        void setStart(sf::Vector2f point_a){mVertices[0].position=point_a;}
        void setEnd(sf::Vector2f point_b){mVertices[1].position=point_b;}
        void setColor(sf::Color color){mVertices[0].color=color;mVertices[1].color=color;}

        void move(sf::Vector2f offset);
        void rotate(float degrees);

    private:
        sf::VertexArray mVertices;
};

#endif
