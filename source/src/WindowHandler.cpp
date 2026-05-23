#include "WindowHandler.h"



WindowHandler::WindowHandler()
{
    _width = 500;
    _height = 500;
    createWindow();
}

WindowHandler::WindowHandler(unsigned int const width = 500, unsigned int const height = 500)
{
    _width = width;
    _height = height;
    createWindow();
}


WindowHandler::~WindowHandler()
{
    if (_window) {
        _window->close();
    }
    delete _window;
    _window = nullptr;
}



void WindowHandler::render()
{


    _window->clear();



}

void WindowHandler::createWindow()
{
    assert(_width);
    assert(_height);
    _window = new sf::RenderWindow(sf::VideoMode({_width, _height}), "SFML Window");
    assert(_window);
}


