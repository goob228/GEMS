#include "Gem.h"
#include "GemBomb.h"

Gem::Gem()
{
    _animState = 0;
    _defaultAnimState = 0;
    _position = fVector2(0,0);
    _animPosition = fVector2(0,0);
    _defaultAnimPosition = fVector2();
    _shape = RectangleShape();
}

Gem::Gem(int const defaultAnimState, DefColor const colorEnum, AnimType const animType, fVector2* const position, fVector2* const defaultAnimPosition)
{
    _animState = 0;
    _defaultAnimState = defaultAnimState;
    _position = *position;
    _animPosition = fVector2(0,0);
    _defaultAnimPosition = *defaultAnimPosition;
    _shape = RectangleShape();
    _animType = animType;
    _colorEnum = colorEnum;
    _shape.setFillColor(getColor(colorEnum));
}

Gem::Gem(std::shared_ptr<Gem> gemptr) : Gem(*gemptr)
{
}

void Gem::draw(WindowHandler* windowHandler)
{
    windowHandler->drawSquare(_shape);
}

void Gem::onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col)
{
    
    int const sizex = gems.size();
    if (sizex == 0) return;
    int const sizey = gems[0].size();

    static std::random_device rd2;
    static std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> distCreate(0, 10);
    if (distCreate(gen2) <= onMatchedChance){
        std::uniform_int_distribution<> distRow(-3, 3);
        std::uniform_int_distribution<> distCol(-3, 3);
        
        int const newx = distRow(gen2) + row;
        int const newy = distCol(gen2) + col;
        if (newx < 0 || newx >= sizex || newy < 0 || newy >= sizey) return;

        std::uniform_int_distribution<> typeOfGem(0, 0);
        int const typeofgem = typeOfGem(gen2);
        if (typeofgem == 0) {
            gems[newx][newy] = std::make_shared<GemBomb>(gems[newx][newy]);
        }
    }
    



}

Color Gem::getColor(DefColor const colorEnum)
{
    switch (colorEnum) {
        case DefColor::RED:      return GameColor::Red;
        case DefColor::BLUE:     return GameColor::Blue;
        case DefColor::CYAN:     return GameColor::Cyan;
        case DefColor::GREEN:    return GameColor::Green;
        case DefColor::PURPLE:   return GameColor::Purple;
        case DefColor::YELLOW:   return GameColor::Yellow;
        case DefColor::ORANGE:   return GameColor::Orange;
        case DefColor::MAGENTA:  return GameColor::Magenta;
        case DefColor::DARKGREEN:return GameColor::Darkgreen;
        default: return GameColor::White;
    }
}



void Gem::update()
{
    updateAnimState();
    updateShapePosition();
}


void Gem::updateShapePosition()
{
    _shape.setPosition(_animPosition + _position);
}

void Gem::setPosition(fVector2& position)
{
    _position = position;
}

void Gem::setDefaultAnimPosition(fVector2& position)
{
    _defaultAnimPosition = position;
}

void Gem::setDefaultAnimState(int const defaultAnimState)
{
    _defaultAnimState = defaultAnimState;
}

void Gem::startAnimation()
{
    _animState = _defaultAnimState;
    _animPosition = _defaultAnimPosition;
}

float Gem::applyEasingFunc(float const t)
{
    switch (_animType){
        case AnimType::LINEAR: {
            return t;
        }
        case AnimType::QUAD_IN: {
            return t * t;
        }
        case AnimType::QUAD_OUT: {
            return (1.0f - (1.0f - t) * (1.0f - t));
        }
        case AnimType::EASE_IN_OUT: {
            return t * t * t * (t * (t * 6 - 15) + 10);;
        }
        case AnimType::OVERSHOOT: {
            const float overshoot = 1.2f;
            return (overshoot + 1.0f) * t * t * t - overshoot * t * t;
        }
    }
    return t;
}

void Gem::updateAnimState()
{
    if (_animState < 0){
        _animState = 0;
    }
    if (_animState == 0){
        _animPosition.y = 0;
        _animPosition.x = 0;
    }
    if (_animState > 0){
        _animState--;
        float t = (float)(_animState)/(float)(_defaultAnimState);
        _animPosition = _defaultAnimPosition * applyEasingFunc(t);
        
    }
}

fVector2 Gem::getCurrentAnimPosition()
{
    return _animPosition;
}