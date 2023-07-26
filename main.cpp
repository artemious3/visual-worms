
#include "SI/Agent.hpp"
#include "SI/SIWindow.hpp"
#include <iostream>
#include "SI/Common.h"



int main(int, char const**)
{
    // Create the main window
    SIWindow window(sf::VideoMode(_WINSIZE, _WINSIZE), "SFML window", _AMOUNT);
    window.update();
    window.display();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        window.clear();
        window.update();
        window.display();
    }
    return EXIT_SUCCESS;
}
