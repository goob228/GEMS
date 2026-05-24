#include "Game.h"

Game::Game()
{
    int width = 600;
    int height = 700;

    _grid = new Grid(width, height);

    _running = false;
    _targetTickRate = 60;
    _windowHandler = new WindowHandler(width, height);
}

Game::~Game()
{
    delete _windowHandler;
    _windowHandler = nullptr;

    delete _grid;
    _grid = nullptr;
}


void Game::respond(std::vector<Event> events)
{
    for (const auto& event : events) {
        switch (event) {
            case Event::CLOSE_WINDOW:
                _running = false;
                break;
            case Event::CLICK_MOUSE:
                iVector2 mousePos = EventHandler::getMousePos(_windowHandler);
                _grid->setSelected(mousePos);
                if (_grid->_selected.x != -1){
                    _grid->_gems[_grid->_selected.x][_grid->_selected.y]->startAnimation();
                }
                #ifndef NDEBUG
                    std::cout << "Clicked X: " << mousePos.x << " Y: " << mousePos.y << std::endl;
                    std::cout << "Selected X: " << _grid->_selected.x << " Y: " << _grid->_selected.y << std::endl;
                #endif
                break;
        }
    }
    _eventHandler._events.clear();
}




void Game::gameLoop()
{   
    _grid->initializeBoard();
    Time time(_targetTickRate);
    _running = true;
    

    while (_running) {
        _eventHandler.handleEvents(_windowHandler);
        respond(_eventHandler._events);
        if (!_running) return;

        update();
        render();
        time.wait();
    }
}

void Game::update()
{
    _grid->update();
}  

void Game::render()
{
    _windowHandler->fill(GameColor::Gray);
    
    _grid->draw(_windowHandler);

    _windowHandler->display();
}   



Game::Time::Time()
{
    int tickRate = 60;
    _tickDuration = std::chrono::milliseconds(1000 / tickRate);
    _lastTime = std::chrono::steady_clock::now();
}

Game::Time::Time(unsigned int const tickRate)
{
    THROW_IF_ZERO(tickRate);
    _tickDuration = std::chrono::milliseconds(1000 / tickRate);
    _lastTime = std::chrono::steady_clock::now();
}

void Game::Time::wait()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - _lastTime;
    if (elapsed < _tickDuration) {
        std::this_thread::sleep_for(_tickDuration - elapsed);
    }
    _lastTime = std::chrono::steady_clock::now();
}