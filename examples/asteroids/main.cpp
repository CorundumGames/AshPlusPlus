#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Declarations.hpp"

using std::srand;
using std::time;

int main()
{
    srand(time(NULL));
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");

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

    return EXIT_SUCCESS;
}
