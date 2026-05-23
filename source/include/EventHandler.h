#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Base.h"

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "WindowHandler.h"



typedef sf::Vector2i iVector2;


enum class Event{
    CLOSE_WINDOW,
    CLICK_MOUSE
};


class EventHandler{

public:

    
    std::vector<Event> _events;

    void handleEvents(WindowHandler* windowHandler);

    static iVector2 getMousePos(WindowHandler* windowHandler);

};



#endif