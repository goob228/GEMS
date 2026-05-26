#include "Grid.h"

Grid::Grid()
{
    int width = 600;
    int height = 700;

    _gridAnimDuration = 60;
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
    _gridAnimDuration = 60;
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
    /*
    for (int row = 0; row < _gems.size(); ++row){
        for (int col = 0; col < _gems[0].size(); ++col){
            delete _gems[row][col];
            _gems[row][col] = nullptr;
        }
    }
        */
}


void Grid::initializeBoard()
{
    fVector2 gridPosition = _gridSquare.getPosition();
    _gems.resize(_gridDimension, std::vector<std::shared_ptr<Gem>>(_gridDimension));
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            fVector2 position = fVector2(row * _cellSize, col * _cellSize) + gridPosition;
            fVector2 defaultAnimPosition(0, -_cellSize*(_gridDimension+3));
            _gems[row][col] = createGem(_gridAnimDuration, generateRandomColor(), &position, &defaultAnimPosition);
            _gems[row][col]->startAnimation();
        }
    }
    _gridAnimCounter = _gridAnimDuration;
}

std::shared_ptr<Gem> Grid::createGem(int const defaultAnimState, DefColor const colorEnum, fVector2* position, fVector2* defaultAnimPosition, AnimType const animType)
{
    Gem* gemptr = new Gem(defaultAnimState, colorEnum, animType, position, defaultAnimPosition);
    gemptr->_shape.setSize(fVector2(_cellSize,_cellSize));
    std::shared_ptr<Gem> sharedptr(gemptr);
    return sharedptr;
}

void Grid::recreateGem(int const x, int const y)
{
    //delete _gems[x][y];
    fVector2 position = fVector2(x*_cellSize,y*_cellSize) + _gridSquare.getPosition();
    fVector2 defaultAnimPosition(0, -_cellSize*(_gridDimension+3));
    _gems[x][y] = createGem(_gridAnimDuration, generateRandomColor(), &position, &defaultAnimPosition);
    _gems[x][y]->startAnimation();
}


DefColor Grid::generateRandomColor()
{

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, DefColorCount-1);
    return static_cast<DefColor>(dist(gen));
    
}



void Grid::onMatchedGems(std::vector<iVector2>& toRemove)
{
    std::vector<iVector2> sorted = toRemove;

    for (const iVector2& pos : sorted) {
        _gems[pos.x][pos.y]->_toRemove = true;
        _gems[pos.x][pos.y]->onMatched(_gems,pos.x,pos.y);
    }
}

void Grid::raiseGems()
{
    
    std::vector<iVector2> sorted;

    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            if (_gems[row][col]->_toRemove) {
                sorted.push_back(iVector2(row,col));
            }
        }
    }

    if (sorted.empty()) return;
    _falling = true;

    std::sort(sorted.begin(), sorted.end(),
              [](const iVector2& a, const iVector2& b) { return a.y < b.y; });


    for (const iVector2& pos : sorted) {
        int x = pos.x;
        int y = pos.y;
        if (x < 0 || x >= (int)_gems.size() || y < 0 || y >= (int)_gems[0].size())
            continue;
        if (_gems[x][y] == nullptr)
            continue;

        // Поднимаем гем до самого верха обмениваясь с верхним соседом
        for (int col = y; col > 0; --col) {
            swapGems(x, col, x, col-1);
            _gems[x][col]->startAnimation();
            _gems[x][col-1]->startAnimation();
            _gridAnimCounter = _gridAnimDuration;
        }
        recreateGem(x,0);
    }
}


bool Grid::hasClusterAt(int const x, int const y) const {
    if (x < 0 || y < 0 || x >= (int)_gems.size() || y >= (int)_gems[0].size())
        return false;
    std::shared_ptr<Gem> start = _gems[x][y];
    if (!start) return false;

    DefColor targetColor = start->_colorEnum;
    int rows = (int)_gems.size();
    int cols = (int)_gems[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::pair<int,int>> stack;
    stack.push_back({x, y});
    visited[x][y] = true;
    int count = 0;

    while (!stack.empty()) {
        auto [cx, cy] = stack.back();
        stack.pop_back();
        ++count;

        // вверх
        if (cx-1 >= 0 && !visited[cx-1][cy] && _gems[cx-1][cy] && _gems[cx-1][cy]->_colorEnum == targetColor) {
            visited[cx-1][cy] = true;
            stack.push_back({cx-1, cy});
        }
        // вниз
        if (cx+1 < rows && !visited[cx+1][cy] && _gems[cx+1][cy] && _gems[cx+1][cy]->_colorEnum == targetColor) {
            visited[cx+1][cy] = true;
            stack.push_back({cx+1, cy});
        }
        // влево
        if (cy-1 >= 0 && !visited[cx][cy-1] && _gems[cx][cy-1] && _gems[cx][cy-1]->_colorEnum == targetColor) {
            visited[cx][cy-1] = true;
            stack.push_back({cx, cy-1});
        }
        // вправо
        if (cy+1 < cols && !visited[cx][cy+1] && _gems[cx][cy+1] && _gems[cx][cy+1]->_colorEnum == targetColor) {
            visited[cx][cy+1] = true;
            stack.push_back({cx, cy+1});
        }
    }
    return count >= 3;
}

bool Grid::wouldMatchAfterSwap(iVector2& first, iVector2& second) {

    if (!_gems[first.x][first.y] || !_gems[second.x][second.y]) {
        return false;
    }

    //временный обмен
    std::swap(_gems[first.x][first.y], _gems[second.x][second.y]);

    // проверяем, появился ли кластер хотя бы у одной из двух клеток
    bool match = hasClusterAt(first.x,first.y) || hasClusterAt(second.x,second.y);

    // откат обмена
    std::swap(_gems[first.x][first.y], _gems[second.x][second.y]);

    return match;
}


std::vector<iVector2> Grid::findClustersToRemove() {
    int rows = (int)_gems.size();
    if (rows == 0) return {};
    int cols = (int)_gems[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<iVector2> toRemove;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

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
                for (int d = 0; d < 4; ++d) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                        !visited[nx][ny] && _gems[nx][ny] != nullptr &&
                        _gems[nx][ny]->_colorEnum == color) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            if (cluster.size() >= 3) {
                toRemove.insert(toRemove.end(), cluster.begin(), cluster.end());
            }
        }
    }
    return toRemove;
}

void Grid::swapGems(iVector2& first, iVector2& second)
{
    std::swap(_gems[first.x][first.y], _gems[second.x][second.y]);
    
    fVector2 temppos1 = _gems[first.x][first.y]->_position;
    fVector2 temppos2 = _gems[second.x][second.y]->_position;
    _gems[first.x][first.y]->setPosition(temppos2);
    _gems[second.x][second.y]->setPosition(temppos1);
    fVector2 temppos3 = temppos1 - temppos2 + _gems[first.x][first.y]->getCurrentAnimPosition();
    fVector2 temppos4 = temppos2 - temppos1 + _gems[second.x][second.y]->getCurrentAnimPosition();
    _gems[first.x][first.y]->setDefaultAnimPosition(temppos3);
    _gems[second.x][second.y]->setDefaultAnimPosition(temppos4);
    
}

void Grid::swapGems(int const x1, int const y1, int const x2, int const y2)
{
    std::swap(_gems[x1][y1], _gems[x2][y2]);
    
    fVector2 temppos1 = _gems[x1][y1]->_position;
    fVector2 temppos2 = _gems[x2][y2]->_position;
    _gems[x1][y1]->setPosition(temppos2);
    _gems[x2][y2]->setPosition(temppos1);
    fVector2 temppos3 = temppos1 - temppos2 + _gems[x1][y1]->getCurrentAnimPosition();
    fVector2 temppos4 = temppos2 - temppos1 + _gems[x2][y2]->getCurrentAnimPosition();
    _gems[x1][y1]->setDefaultAnimPosition(temppos3);
    _gems[x2][y2]->setDefaultAnimPosition(temppos4);
    
}

bool Grid::areNeighbours(iVector2& first, iVector2& second)
{

    return (std::abs(first.x - second.x) + std::abs(first.y - second.y) == 1);
}


void Grid::updateSelected(iVector2& mousePos)
{
    iVector2 newSelected = getSelected(mousePos);
    if (_selected == newSelected || _falling){
        if (_selected.x != -1) {
            _gems[_selected.x][_selected.y]->resetShapeOutline();
        }
        _selected.x = -1;
        _selected.y = -1;
        
        return;
    }
    if ( newSelected.x != -1 && _selected.x != -1) {
        if (!_falling && areNeighbours(_selected, newSelected) && wouldMatchAfterSwap(_selected, newSelected)) {
            swapGems(_selected, newSelected);
            _gems[_selected.x][_selected.y]->startAnimation();
            _gems[newSelected.x][newSelected.y]->startAnimation();
            _gems[_selected.x][_selected.y]->resetShapeOutline();
            _gems[newSelected.x][newSelected.y]->resetShapeOutline();
            _gridAnimCounter = _gridAnimDuration;
            _selected.x = -1;
            _selected.y = -1;
            return;
        }
    }
    if (_selected.x != -1) {
        _gems[_selected.x][_selected.y]->resetShapeOutline();
    }
    if (newSelected.x != -1) {
        _gems[newSelected.x][newSelected.y]->setShapeOutline();
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

void Grid::updateAnimCounter()
{
    if (_gridAnimCounter > 0) _gridAnimCounter--;
    if (_gridAnimCounter < 0) _gridAnimCounter = 0;
}

void Grid::update()
{      
    if (_gridAnimCounter == 0) {
        _falling = false;
        std::vector<iVector2> toRemove = findClustersToRemove();
        if (!toRemove.empty()){
            onMatchedGems(toRemove);
        }
    }
    
    raiseGems();

    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            _gems[row][col]->update();
        }
    }

    updateAnimCounter();
}

void Grid::draw(WindowHandler* windowHandler)
{
    windowHandler->drawSquare(_gridSquare);
    
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            _gems[row][col]->draw(windowHandler);
        }
    }

    //отдельно рисуем выбранный гем, чтобы его внешняя обводка перекрывала остальных
    if (_selected.x != -1) {
        _gems[_selected.x][_selected.y]->draw(windowHandler);
    }
}
