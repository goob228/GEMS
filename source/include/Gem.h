#ifndef GEM_H
#define GEM_H

#include "SFMLtypes.h"

int const DefColorCount = 9;
enum class DefColor{
    RED,
    BLUE,
    CYAN,
    GREEN,
    PURPLE,
    YELLOW,
    ORANGE,
    MAGENTA,
    DARKGREEN
};

enum class AnimType{
    LINEAR,
    QUAD_IN,
    QUAD_OUT,
    EASE_IN_OUT,
    OVERSHOOT
};

class Gem{

    friend class Grid;

public:

    Gem();
    Gem(int defaultAnimState, DefColor colorEnum, fVector2* position, fVector2* defaultAnimPosition, AnimType animType);
    
    void update();
    void setPosition(fVector2& position);
    void setDefaultAnimPosition(fVector2& position);
    void setDefaultAnimState(int defaultAnimState);
    void startAnimation();

    fVector2 getCurrentAnimPosition();

    

private:
    
    Color getColor(DefColor colorEnum);
    void updateAnimState();
    void updateShapePosition();
    float applyEasingFunc(float t);

    int _animState;
    int _defaultAnimState;
    AnimType _animType;

    fVector2 _position;
    fVector2 _animPosition;
    fVector2 _defaultAnimPosition;

    DefColor _colorEnum;
    RectangleShape _shape;
};

#endif