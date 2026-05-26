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