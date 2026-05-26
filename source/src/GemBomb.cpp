#include "GemBomb.h"

GemBomb::GemBomb(int const defaultAnimState, DefColor const colorEnum, AnimType const animType, 
    fVector2* const position, fVector2* const defaultAnimPosition)
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
    _specificShape = CircleShape();
    _specificShape.setFillColor(Color::Black);
}

GemBomb::GemBomb(std::shared_ptr<Gem> gemptr) : Gem(*gemptr)
{
    _specificShape = CircleShape();
    _specificShape.setFillColor(Color::Black);
}

void GemBomb::draw(WindowHandler* windowHandler)
{
    Gem::draw(windowHandler);
    windowHandler->drawCircle(_specificShape);
}

void GemBomb::updateShapePosition()
{
    Gem::updateShapePosition();
    fVector2 size = _shape.getSize();
    size = size*0.25f;
    _specificShape.setRadius(size.x);
    _specificShape.setPosition(_animPosition + _position + size);
}

void GemBomb::onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col)
{   
    Gem::onMatched(gems, row, col);

    int const sizex = gems.size();
    if (sizex == 0) return;
    int const sizey = gems[0].size();

    static std::random_device rd2;
    static std::mt19937 gen2(rd2());
    
    std::uniform_int_distribution<> distRow(0, sizex-1);
    std::uniform_int_distribution<> distCol(0, sizey-1);
    
    for (int i = 0; i < 5; i++) {
        int newx = distRow(gen2);
        int newy = distCol(gen2);
        gems[newx][newy]->_toRemove = true;
    }



}