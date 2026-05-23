#include "EventHandler.h"



void EventHandler::handleEvents(WindowHandler& window_handler)
{   

    sf::Event event;

    while (window_handler.window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_handler.window->close();
            events.push_back(Event::Close_Window);
        }
    }

}