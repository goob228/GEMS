#ifndef WINDOWHANDLERH
#define WINDOWHANDLERH

#include "SFML/Graphics.hpp"




class WindowHandler{

public:


    WindowHandler();
    ~WindowHandler();

    sf::RenderWindow* m_window;

    void render();



};




#endif