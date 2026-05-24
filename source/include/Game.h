#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "EventHandler.h"
#include "Grid.h"

#include <chrono>
#include <thread>





class Game {

public:
    
    Game();
    ~Game();

    void gameLoop();

private:

    void respond(std::vector<Event> events);

    void update();
    void render();
    
    /*
    * Essentials
    */
    bool _running;
    unsigned int _targetTickRate;
    WindowHandler* _windowHandler;
    EventHandler _eventHandler;

    /*
    * Gem Related
    */
    Grid* _grid;
    
    

    class Time {
    public:

        Time();
        Time(unsigned int const tickRate);

        void wait();

    private:
        std::chrono::steady_clock::duration _tickDuration;
        std::chrono::steady_clock::time_point _lastTime;
    };


};


#endif