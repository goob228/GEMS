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
    


    //void fillBoard();


};


#endif