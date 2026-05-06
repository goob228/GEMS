#ifndef GAMEH
#define GAMEH
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