#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera();
        ~Camera();

        void moveTo(sf::Vector2f newCenter);
        void follow(sf::Vector2f center);
        void setCenter(sf::Vector2f center){mCenter=center;mView.setCenter(mCenter);}
        void zoom(float factor){mView.zoom(factor);}

        sf::Vector2f getChange(){return mOldCenter-mCenter;} // returns the distance between teh two camera centers
        sf::Vector2f getCenter(){return mCenter;}
        sf::View& getView(){return mView;}

    private:
        sf::Vector2f mOldCenter; // to keep track of change
        sf::Vector2f mCenter;
        sf::View mView;
};

#endif // CAMERA_H
