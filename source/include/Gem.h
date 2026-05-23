#ifndef GEM_H
#define GEM_H

#include "SFMLtypes.h"

class Gem{

private:
    
    int _animState;

    iVector2 _position;
    fVector2 _animPosition;

    Color _color;
    RectangleShape _shape;
}

#endif