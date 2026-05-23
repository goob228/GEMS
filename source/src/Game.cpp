#include "Game.h"



void Game::respond(std::vector<Event> events)
{
    for (const auto& event : events) {
        switch (event) {
            case Event::Close_Window:
                running = false;
                break;
            case Event::Click_Mouse:
                


            
                break;
            default:
                // Code to execute if no cases match
                break;
        }
    }


}


void Game::gameLoop()
{

    running = true;


    while (running) {

        event_handler.handleEvents(window_handler);
        respond(event_handler.events);

        window_handler.render();
    }
}



Game::Game()
{
    running = false;
}

Game::~Game() {}