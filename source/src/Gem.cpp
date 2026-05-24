#include "Gem.h"

Gem::Gem()
{
    _animState = 0;
    _defaultAnimState = 0;
    _position = fVector2(0,0);
    _animPosition = fVector2(0,0);
    _defaultAnimPosition = fVector2();
    _shape = RectangleShape();
}

Gem::Gem(int defaultAnimState, DefColor colorEnum, fVector2* position, fVector2* defaultAnimPosition)
{
    _animState = 0;
    _defaultAnimState = defaultAnimState;
    _position = *position;
    _animPosition = fVector2(0,0);
    _defaultAnimPosition = *defaultAnimPosition;
    _shape = RectangleShape();
    _colorEnum = colorEnum;
    _shape.setFillColor(getColor(colorEnum));
}

Color Gem::getColor(DefColor colorEnum)
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

void Gem::setDefaultAnimState(int defaultAnimState)
{
    _defaultAnimState = defaultAnimState;
}

void Gem::startAnimation()
{
    _animState = _defaultAnimState;
    _animPosition = _defaultAnimPosition;
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
        _animPosition = _defaultAnimPosition*((float)(_animState)/(float)(_defaultAnimState));
    }
}

fVector2 Gem::getCurrentAnimPosition()
{
    return _animPosition;
}