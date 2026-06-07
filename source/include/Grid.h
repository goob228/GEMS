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

    int _score = 0;

private:

    std::shared_ptr<Gem> createGem(int const defaultAnimState, DefColor const colorEnum, fVector2* position, fVector2* defaultAnimPosition, 
        AnimType const animType = AnimType::QUAD_IN);
    DefColor generateRandomColor();
    void onMatchedGems(std::vector<iVector2>& toRemove);
    void raiseGems();
    bool hasClusterAt(int const x, int const y) const;
    bool wouldMatchAfterSwap(iVector2& first, iVector2& second);
    std::vector<iVector2> findClustersToRemove();
    void swapGems(int const x1, int const y1, int const x2, int const y2);
    void swapGems(iVector2& first, iVector2& second);
    void recreateGem(int const x, int const y);
    bool areNeighbours(iVector2& first, iVector2& second);
    void updateAnimCounter();
    


    int _gridAnimDuration;
    int _gridAnimCounter;
    bool _falling;
    int _gridDimension;
    float _cellSize;
    iVector2 _selected;
    RectangleShape _gridSquare;
    std::vector<std::vector<std::shared_ptr<Gem>>> _gems;
};


#endif
