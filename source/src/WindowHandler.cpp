#include "WindowHandler.h"



WindowHandler::WindowHandler()
{
    _width = 500;
    _height = 500;
    createWindow();
}

WindowHandler::WindowHandler(unsigned int const width, unsigned int const height)
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

void WindowHandler::fill(Color color)
{
    _window->clear(color);
}

void WindowHandler::drawSquare(RectangleShape &shape)
{
    _window->draw(shape);
}

void WindowHandler::display()
{
    _window->display();
}


void WindowHandler::render()
{
    _window->clear(GameColor::Gray);


    _window->display();
}

void WindowHandler::createWindow()
{
    assert(_width);
    assert(_height);
    _window = new sf::RenderWindow(sf::VideoMode({_width, _height}), "Gems Game", sf::Style::Close);
    assert(_window);
}


