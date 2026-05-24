#include "Gem.h"

Gem::Gem()
{
    _animState = 0;
    _defaultAnimState = 0;
    _position = fVector2(0,0);
    _animPosition = fVector2(0,0);
    _defaultAnimPosition = fVector2();
    _color = Color();
    _shape = RectangleShape();
}

Gem::Gem(int defaultAnimState, fVector2* position, fVector2* defaultAnimPosition, Color* color)
{
    _animState = 0;
    _defaultAnimState = defaultAnimState;
    _position = *position;
    _animPosition = fVector2(0,0);
    _defaultAnimPosition = *defaultAnimPosition;
    _color = *color;
    _shape = RectangleShape();
    _shape.setFillColor(*color);
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