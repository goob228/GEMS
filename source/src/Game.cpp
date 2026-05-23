#include "Game.h"



void Game::respond(std::vector<Event> events)
{
    for (const auto& event : events) {
        switch (event) {
            case Event::CLOSE_WINDOW:
                _running = false;
                break;
            case Event::CLICK_MOUSE:
                iVector2 mousePos = EventHandler::getMousePos(_windowHandler);
                #ifndef NDEBUG
                    std::cout << "Clicked X: " << mousePos.x << " Y: " << mousePos.y << std::endl;
                #endif
                break;
        }
    }

    _eventHandler._events.clear();


}


void Game::gameLoop()
{
    Time time(_targetTickRate);
    _running = true;

    while (_running) {
        _eventHandler.handleEvents(_windowHandler);
        respond(_eventHandler._events);
        if (!_running) return;

        render();
        time.wait();
    }
}

void Game::render()
{
    _windowHandler->fill(Color::Gray);
    _windowHandler->drawSquare(_gridSquare);

    _windowHandler->display();
}


Game::Game()
{
    int width = 600;
    int height = 700;
    _gridSquare = RectangleShape();
    _gridSquare.setSize(fVector2(width,width));
    _gridSquare.setPosition(0,height-width);
    _gridSquare.setFillColor(Color::Black);

    _running = false;
    _targetTickRate = 60;
    _windowHandler = new WindowHandler(width, height);
}

Game::~Game()
{
    delete _windowHandler;
    _windowHandler = nullptr;
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