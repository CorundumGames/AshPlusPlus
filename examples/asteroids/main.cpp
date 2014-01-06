#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Declarations.hpp"

#include "asteroids/include/Asteroids.hpp"

using std::make_shared;
using std::shared_ptr;
using std::srand;
using std::time;

using sf::RenderWindow;

const int WIDTH = 640;
const int HEIGHT = 480;

int main()
{
    srand(time(NULL));

    // Create the main window
    shared_ptr<RenderWindow> window(make_shared<RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "SFML window"));
    net::richardlord::asteroids::Asteroids game(window, WIDTH, HEIGHT);

    game.start();
/*
    // Load a sprite to display
    sf::Texture texture;

    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;

    sf::Sprite Sprite(texture);

	// Start the game loop
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        // Clear screen
        App.clear();

        // Draw the sprite
        App.draw(Sprite);

        // Update the window
        App.display();
    }
    */

    return EXIT_SUCCESS;
}
