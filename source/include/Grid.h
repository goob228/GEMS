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
    void updateSelected(iVector2& mousePos);
    iVector2 getSelected(iVector2& mousePos);
    void update();
    void draw(WindowHandler* windowHandler);

private:

    Gem* createGem(int defaultAnimState, DefColor colorEnum, fVector2* position, fVector2* defaultAnimPosition);
    DefColor generateRandomColor();
    void swapGems(iVector2& first, iVector2& second);
    bool areNeighbours(iVector2& first, iVector2& second);

    int _gridDimension;
    float _cellSize;
    iVector2 _selected;
    RectangleShape _gridSquare;
    std::vector<std::vector<Gem*>> _gems;
};


#endif
