#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Player.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing Ball with Chipmunk2D");
    window.setFramerateLimit(60);


    Player player;




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update();

        window.clear(sf::Color::Black);
        player.draw(window);
        window.display();
    }


    return 0;
}
