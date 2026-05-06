#include "Game.h"



void Game::gameLoop()
{

    running = true;

    int i = 0;
    while (running) {

        if (!window_handler.m_window->isOpen()) {
            running = false;
        }

        EventHandler::handleEvent(window_handler.m_window);
        window_handler.render();


        
    }


}


Game::Game()
{
    running = false;
}

Game::~Game() {}