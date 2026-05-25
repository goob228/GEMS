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

    Gem* createGem(int defaultAnimState, DefColor colorEnum, fVector2* position, fVector2* defaultAnimPosition, 
        AnimType animType = AnimType::QUAD_IN);
    DefColor generateRandomColor();
    void raiseGems(std::vector<iVector2>& toRemove);
    bool hasClusterAt(int x, int y) const;
    bool wouldMatchAfterSwap(iVector2& first, iVector2& second);
    std::vector<iVector2> findClustersToRemove();
    void swapGems(int x1, int y1, int x2, int y2);
    void swapGems(iVector2& first, iVector2& second);
    void recreateGem(int x, int y);
    bool areNeighbours(iVector2& first, iVector2& second);
    void updateAnimCounter();

    int _gridAnimDuration;
    int _gridAnimCounter;
    bool _falling;
    int _gridDimension;
    float _cellSize;
    iVector2 _selected;
    RectangleShape _gridSquare;
    std::vector<std::vector<Gem*>> _gems;
};


#endif
