#ifndef GAMEH
#define GAMEH
#include "window.h"


class Game {

public:
    
    Game();
    ~Game();

    void gameLoop();

private:

    bool running;
    
    Window window;


    //void fillBoard();


};


#endif