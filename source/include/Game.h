#ifndef GAME_H
#define GAME_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"
#include "EventHandler.h"
#include "Gem.h"

#include <chrono>
#include <thread>





class Game {

public:
    
    Game();
    ~Game();

    void gameLoop();

private:

    void initializeBoard();

    Color generateRandomColor();
    Gem* createGem(int defaultAnimState, fVector2* position, fVector2* defaultAnimPosition, Color* color);

    void respond(std::vector<Event> events);

    void render();

    int _gridDimension;
    RectangleShape _gridSquare;
    std::vector<std::vector<Gem*>> _gems;

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