#ifndef GEMPAINT_H
#define GEMPAINT_H

#include "Gem.h"


class GemPaint: public Gem {

public:

    explicit GemPaint(std::shared_ptr<Gem> gemptr);

    void draw(WindowHandler* windowHandler) override;
    void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col) override;

protected:
    
    void updateShapePosition() override;
    
    CircleShape _specificShape;

};


#endif