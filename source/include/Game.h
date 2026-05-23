#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "WindowHandler.h"
#include "EventHandler.h"

#include <chrono>
#include <thread>


class Game {

public:
    
    Game();
    ~Game();

    void gameLoop();

private:

    void respond(std::vector<Event> events);



    bool _running;
    unsigned int _targetTickRate;
    WindowHandler* _windowHandler;
    EventHandler _eventHandler;

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