#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "SFML/Graphics.hpp"
#include "WindowHandler.h"


enum class Event{
    CloseWindow
};


class EventHandler{

public:


    static void handleEvent(WindowHandler& window_handler);


};



#endif