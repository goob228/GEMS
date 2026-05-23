#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include "Base.h"

#include "SFML/Graphics.hpp"




class WindowHandler{

    friend class EventHandler;

public:

    WindowHandler();
    WindowHandler(unsigned int const width, unsigned int const height);
    ~WindowHandler();

   

    void createWindow();

    void render();

private:

    unsigned int _width;
    unsigned int _height;

    sf::RenderWindow* _window;



};




#endif