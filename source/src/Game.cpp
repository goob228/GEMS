#include "Game.h"

Game::Game()
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

    _running = false;
    _targetTickRate = 60;
    _windowHandler = new WindowHandler(width, height);
}

Game::~Game()
{
    delete _windowHandler;
    _windowHandler = nullptr;

    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            delete _gems[row][col];
        }
    }
}


void Game::initializeBoard()
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

Color Game::generateRandomColor()
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

Gem* Game::createGem(int defaultAnimState, fVector2* position, fVector2* defaultAnimPosition, Color* color)
{
    Gem* gemptr = new Gem(defaultAnimState, position, defaultAnimPosition, color);
    return gemptr;
}

void Game::respond(std::vector<Event> events)
{
    for (const auto& event : events) {
        switch (event) {
            case Event::CLOSE_WINDOW:
                _running = false;
                break;
            case Event::CLICK_MOUSE:
                iVector2 mousePos = EventHandler::getMousePos(_windowHandler);
                setSelected(mousePos);
                if (_selected.x != -1){
                    _gems[_selected.x][_selected.y]->startAnimation();
                }
                #ifndef NDEBUG
                    std::cout << "Clicked X: " << mousePos.x << " Y: " << mousePos.y << std::endl;
                    std::cout << "Selected X: " << _selected.x << " Y: " << _selected.y << std::endl;
                #endif
                break;
        }
    }
    _eventHandler._events.clear();
}

void Game::setSelected(iVector2 mousePos)
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


void Game::gameLoop()
{   
    initializeBoard();
    Time time(_targetTickRate);
    _running = true;
    

    while (_running) {
        _eventHandler.handleEvents(_windowHandler);
        respond(_eventHandler._events);
        if (!_running) return;

        render();
        time.wait();
    }
}

void Game::render()
{
    _windowHandler->fill(GameColor::Gray);
    _windowHandler->drawSquare(_gridSquare);
    
    for (int row = 0; row < _gridDimension; ++row){
        for (int col = 0; col < _gridDimension; ++col){
            _gems[row][col]->update();
            _windowHandler->drawSquare(_gems[row][col]->_shape);
        }
    }

    _windowHandler->display();
}   



Game::Time::Time()
{
    int tickRate = 60;
    _tickDuration = std::chrono::milliseconds(1000 / tickRate);
    _lastTime = std::chrono::steady_clock::now();
}

Game::Time::Time(unsigned int const tickRate)
{
    THROW_IF_ZERO(tickRate);
    _tickDuration = std::chrono::milliseconds(1000 / tickRate);
    _lastTime = std::chrono::steady_clock::now();
}

void Game::Time::wait()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - _lastTime;
    if (elapsed < _tickDuration) {
        std::this_thread::sleep_for(_tickDuration - elapsed);
    }
    _lastTime = std::chrono::steady_clock::now();
}