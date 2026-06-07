#include "GemPaint.h"


GemPaint::GemPaint(std::shared_ptr<Gem> gemptr) : Gem(*gemptr)
{
    _shape.setFillColor(getColor(_colorEnum));
    _specificShape = CircleShape();
    _specificShape.setFillColor(Color::White);
}

void GemPaint::draw(WindowHandler* windowHandler)
{
    Gem::draw(windowHandler);
    windowHandler->drawCircle(_specificShape);
}

void GemPaint::updateShapePosition()
{
    Gem::updateShapePosition();
    fVector2 size = _shape.getSize();
    size = size*0.25f;
    _specificShape.setRadius(size.x);
    _specificShape.setPosition(_animPosition + _position + size);
}

void GemPaint::onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col)
{   
    Gem::onMatched(gems, row, col);

    int const sizex = gems.size();
    if (sizex == 0) return;
    int const sizey = gems[0].size();

    static std::random_device rd2;
    static std::mt19937 gen2(rd2());
    
    std::uniform_int_distribution<> distRow(0, sizex-1);
    std::uniform_int_distribution<> distCol(0, sizey-1);
    int counter = 0;
    for (int i = 0; i < sizex*sizey; i++) {
        int newx = distRow(gen2);
        int newy = distCol(gen2);
        if ((std::abs(newx - row) + std::abs(newy - col) <= 1)) continue; //Должны быть не соседи
        counter++;
        gems[newx][newy]->_colorEnum = _colorEnum;
        gems[newx][newy]->_shape.setFillColor(getColor(_colorEnum));
        if (counter >= 2) break;
    }



}