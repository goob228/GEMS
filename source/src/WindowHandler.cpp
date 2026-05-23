#include "WindowHandler.h"

#ifndef NDEBUG
#include <iostream>
#endif






void WindowHandler::render()
{


#ifdef _DEBUG
    std::cout << 1 << std::endl;
#endif

    window->clear();
        



}







WindowHandler::WindowHandler()
{
    window = new sf::RenderWindow(sf::VideoMode({800, 600}), "SFML Window");
}
WindowHandler::~WindowHandler()
{
    delete window;
}