#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


int main()
{
   // Init game engine
    Game game();

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    //game loop
        while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}