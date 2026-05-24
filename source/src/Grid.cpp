#include "Grid.h"

Grid::Grid()
{
    int width = 600;
    int height = 700;

    _gridAnimDuration = 30;
    _gridAnimCounter = 0;
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
    _gridAnimDuration = 30;
    _gridAnimCounter = 0;
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
            fVector2 position = fVector2(row * cellSize, col * cellSize) + gridPosition;
            fVector2 defaultAnimPosition = fVector2(0, -cellSize*(_gridDimension+3));
            _gems[row][col] = createGem(_gridAnimDuration, generateRandomColor(), &position, &defaultAnimPosition);
            _gems[row][col]->_shape.setSize(fVector2(cellSize,cellSize));
            _gems[row][col]->startAnimation();
        }
    }
}

Gem* Grid::createGem(int defaultAnimState, DefColor colorEnum, fVector2* position, fVector2* defaultAnimPosition)
{
    Gem* gemptr = new Gem(defaultAnimState, colorEnum, position, defaultAnimPosition);
    return gemptr;
}

DefColor Grid::generateRandomColor()
{

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, DefColorCount-1);
    return static_cast<DefColor>(dist(gen));
    
}
/*
std::vector<iVector2> Grid::findClustersToRemove() {
    int rows = _gridDimension;
    int cols = _gridDimension;
    

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<iVector2> toRemove;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (visited[i][j] || _gems[i][j] == nullptr) continue;

            DefColor color = _gems[i][j]->_colorEnum;
            std::vector<iVector2> cluster;
            std::queue<iVector2> q;
            q.push({i, j});
            visited[i][j] = true;

            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                cluster.push_back({x, y});

                // 4 соседа (вверх, вниз, влево, вправо)
                int dx[] = {1, -1, 0, 0};
                int dy[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                        !visited[nx][ny] && _gems[nx][ny] != nullptr &&
                        _gems[nx][ny]->_colorEnum == color) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }

            // Если в кластере 3 или более гема – добавляем все его координаты в список на удаление
            if (cluster.size() >= 3) {
                toRemove.insert(toRemove.end(), cluster.begin(), cluster.end());
            }
        }
    }
    return toRemove;
}*/

void Grid::swapGems(iVector2& first, iVector2& second)
{
    Gem* tempptr = _gems[first.x][first.y];
    _gems[first.x][first.y] = _gems[second.x][second.y];
    _gems[second.x][second.y] = tempptr;
    
    fVector2 temppos1 = _gems[first.x][first.y]->_position;
    fVector2 temppos2 = _gems[second.x][second.y]->_position;
    _gems[first.x][first.y]->setPosition(temppos2);
    _gems[second.x][second.y]->setPosition(temppos1);
    fVector2 temppos3 = temppos1 - temppos2 + _gems[first.x][first.y]->getCurrentAnimPosition();
    fVector2 temppos4 = temppos2 - temppos1 + _gems[second.x][second.y]->getCurrentAnimPosition();
    _gems[first.x][first.y]->setDefaultAnimPosition(temppos3);
    _gems[second.x][second.y]->setDefaultAnimPosition(temppos4);
    
}

bool Grid::areNeighbours(iVector2& first, iVector2& second)
{

    return (std::abs(first.x - second.x) + std::abs(first.y - second.y) == 1);
}


void Grid::updateSelected(iVector2& mousePos)
{
    iVector2 newSelected = getSelected(mousePos);
    if ( newSelected.x != -1 && _selected.x != -1) {
        if (areNeighbours(_selected, newSelected)) {
            swapGems(_selected, newSelected);
            _gems[_selected.x][_selected.y]->startAnimation();
            _gems[newSelected.x][newSelected.y]->startAnimation();
            _selected.x = -1;
            _selected.y = -1;
            return;
        }
    }
    _selected = newSelected;
}

iVector2 Grid::getSelected(iVector2& mousePos)
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

    iVector2 selected(idx, idy);

    return selected;

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
