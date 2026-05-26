#ifndef GEMPAINT_H
#define GEMPAINT_H

#include "Gem.h"


class GemPaint: public Gem {

public:

    GemPaint(int const defaultAnimState, DefColor const colorEnum, AnimType const animType, 
        fVector2* const position, fVector2* const defaultAnimPosition);

    explicit GemPaint(std::shared_ptr<Gem> gemptr);

    void draw(WindowHandler* windowHandler) override;
    void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col) override;

protected:
    
    void updateShapePosition() override;
    
    CircleShape _specificShape;

};


#endif