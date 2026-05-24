#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include "Base.h"
#include "SFMLtypes.h"




class WindowHandler{

    friend class EventHandler;

public:

    WindowHandler();
    WindowHandler(unsigned int const width, unsigned int const height);
    ~WindowHandler();

    void fill(Color color);
    
    void drawSquare(RectangleShape &shape);

    void display();

    void createWindow();

    void render();

private:

    unsigned int _width;
    unsigned int _height;

    sf::RenderWindow* _window;



};




#endif