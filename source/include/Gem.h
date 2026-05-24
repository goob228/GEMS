#ifndef GEM_H
#define GEM_H

#include "SFMLtypes.h"

int const DefColorCount = 10;
enum class DefColor{
    RED,
    BLUE,
    CYAN,
    GREEN,
    HAZEL,
    PURPLE,
    YELLOW,
    ORANGE,
    MAGENTA,
    DARKGREEN
};

enum class AnimType{
    LERP
};

class Gem{

    friend class Game;

public:

    Gem();
    Gem(int defaultAnimState, fVector2* position, fVector2* defaultAnimPosition, Color* color);
    
    void update();
    void setPosition(fVector2 position);
    void setDefaultAnimPosition(fVector2 position);
    void setDefaultAnimState(int defaultAnimState);
    void startAnimation();

    

private:
    
    void updateAnimState();
    void updateShapePosition();

    int _animState;
    int _defaultAnimState;

    fVector2 _position;
    fVector2 _animPosition;
    fVector2 _defaultAnimPosition;

    Color _color;
    RectangleShape _shape;
};

#endif