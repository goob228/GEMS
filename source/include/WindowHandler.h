#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include "SFML/Graphics.hpp"




class WindowHandler{

public:


    WindowHandler();
    ~WindowHandler();

    sf::RenderWindow* window;

    void render();



};




#endif