#include "Grid.h"

Grid::Grid()
{
    int width = 600;
    int height = 700;

    _gridDimension = 10;
    _cellSize = width/_gridDimension;
    _selected = iVector2(-1,-1);
    _gridSquare = RectangleShape();
    _gridSquare.setSize(fVector2(width,width));
    _gridSquare.setPosition(0,height-width);
    _gridSquare.setFillColor(GameColor::Black);

}

Grid::Grid(int const width, int const height)
{
    _gridDimension = 10;
    _cellSize = width/_gridDimension;
    _selected = iVector2(-1,-1);
    _gridSquare = RectangleShape();
    _gridSquare.setSize(fVector2(width,width));
    _gridSquare.setPosition(0,height-width);
    _gridSquare.setFillColor(GameColor::Black);
}

Grid::~Grid()
{
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            delete _gems[row][col];
            _gems[row][col] = nullptr;
        }
    }
}


void Grid::initializeBoard()
{
    float cellSize = _cellSize;
    fVector2 gridPosition = _gridSquare.getPosition();
    _gems.resize(_gridDimension, std::vector<Gem*>(_gridDimension));
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            Color color = generateRandomColor();
            fVector2 position = fVector2(row * cellSize, col * cellSize) + gridPosition;
            fVector2 defaultAnimPosition = fVector2(0, -cellSize*(_gridDimension+3));
            _gems[row][col] = createGem(60, &position, &defaultAnimPosition, &color);
            _gems[row][col]->_shape.setSize(fVector2(cellSize,cellSize));
            _gems[row][col]->startAnimation();
        }
    }
}

Gem* Grid::createGem(int defaultAnimState, fVector2* position, fVector2* defaultAnimPosition, Color* color)
{
    Gem* gemptr = new Gem(defaultAnimState, position, defaultAnimPosition, color);
    return gemptr;
}

Color Grid::generateRandomColor()
{

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, DefColorCount-1);
    switch (static_cast<DefColor>(dist(gen))) {
        case DefColor::RED:      return GameColor::Red;
        case DefColor::BLUE:     return GameColor::Blue;
        case DefColor::CYAN:     return GameColor::Cyan;
        case DefColor::GREEN:    return GameColor::Green;
        case DefColor::HAZEL:    return GameColor::Hazel;
        case DefColor::PURPLE:   return GameColor::Purple;
        case DefColor::YELLOW:   return GameColor::Yellow;
        case DefColor::ORANGE:   return GameColor::Orange;
        case DefColor::MAGENTA:  return GameColor::Magenta;
        case DefColor::DARKGREEN:return GameColor::Darkgreen;
        default: return GameColor::White;
    }
}

void Grid::setSelected(iVector2& mousePos)
{
    fVector2 gridPosition = _gridSquare.getPosition();
    int newx = mousePos.x - (int)(gridPosition.x);
    int newy = mousePos.y - (int)(gridPosition.y);

    int idx = newx / (int)(_cellSize);
    int idy = newy / (int)(_cellSize);

    // Если координата за пределами поля то она равна -1
    idx = (newx < 0 || idx >= _gridDimension) ? -1 : idx;
    idy = (newy < 0 || idy >= _gridDimension) ? -1 : idy;

    // Если одна координата равна -1 то все будут равны -1
    idx = (idy == -1) ? -1 : idx;
    idy = (idx == -1) ? -1 : idy;

    _selected.x = idx;
    _selected.y = idy;

}

void Grid::update()
{
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            _gems[row][col]->update();
        }
    }
}

void Grid::draw(WindowHandler* windowHandler)
{
    windowHandler->drawSquare(_gridSquare);
    
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            windowHandler->drawSquare(_gems[row][col]->_shape);
        }
    }
}
