#include "Game.h"




void Game::gameLoop()
{

    running = true;

    int i = 0;
    while (running) {

        window.render();


        i++;
        if (i > 5) {
            running = false;
        }
    }


}


Game::Game()
{
    running = false;
}

Game::~Game() {}