#ifndef GAME_H
#define GAME_H
#include "WindowHandler.h"
#include "EventHandler.h"


class Game {

public:
    
    Game();
    ~Game();

    void gameLoop();

private:

    bool running;
    
    WindowHandler window_handler;
    EventHandler event_handler;
    
    void respond(std::vector<Event> events);

    //void fillBoard();


};


#endif