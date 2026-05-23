#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "SFML/Graphics.hpp"
#include "WindowHandler.h"

#include <vector>


enum class Event{
    Close_Window,
    Click_Mouse
};


class EventHandler{

public:

    
    std::vector<Event> events;

    void handleEvents(WindowHandler& window_handler);

    static void getMousePos(WindowHandler& window_handler);

};



#endif