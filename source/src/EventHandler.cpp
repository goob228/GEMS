#include "EventHandler.h"



void EventHandler::handleEvent(sf::RenderWindow* window)
{   

    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }

}