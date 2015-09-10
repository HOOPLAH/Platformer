#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <SFML/Graphics.hpp>

class LevelEditor
{
    public:
        LevelEditor();
        ~LevelEditor();

        void update(int ticks);
        void draw(sf::RenderTarget& target, float alpha);
        void handleEvents(sf::Event& event);

    private:

};

#endif // LEVELEDITOR_H
