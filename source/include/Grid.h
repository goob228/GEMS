#ifndef GRID_H
#define GRID_H

#include "Base.h"
#include "SFMLtypes.h"
#include "Gem.h"
#include "WindowHandler.h"

class Grid {

    friend class Game;

public:
    Grid();
    Grid(int const width, int const height);
    ~Grid();

    void initializeBoard();
    void setSelected(iVector2& mousePos);
    void update();
    void draw(WindowHandler* windowHandler);

private:

    Gem* createGem(int defaultAnimState, fVector2* position, fVector2* defaultAnimPosition, Color* color);
    Color generateRandomColor();

    int _gridDimension;
    float _cellSize;
    iVector2 _selected;
    RectangleShape _gridSquare;
    std::vector<std::vector<Gem*>> _gems;
};


#endif
