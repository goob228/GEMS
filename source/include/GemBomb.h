#ifndef GEMBOMB_H
#define GEMBOMB_H

#include "Gem.h"


class GemBomb: public Gem {

public:

    GemBomb(int const defaultAnimState, DefColor const colorEnum, AnimType const animType, 
        fVector2* const position, fVector2* const defaultAnimPosition);

    explicit GemBomb(std::shared_ptr<Gem> gemptr);

    void draw(WindowHandler* windowHandler) override;
    void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col) override;

protected:
    
    void updateShapePosition() override;
    
    CircleShape _specificShape;

};


#endif