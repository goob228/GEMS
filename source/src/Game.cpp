#include "Game.h"



void Game::gameLoop()
{

    running = true;

    int i = 0;
    while (running) {

        if (!window_handler.window->isOpen()) {
            running = false;
        }

        EventHandler::handleEvent(window_handler);
        window_handler.render();


        
    }


}


Game::Game()
{
    running = false;
}

Game::~Game() {}