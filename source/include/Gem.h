#ifndef GEM_H
#define GEM_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"


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
    Gem(int const defaultAnimState, DefColor const colorEnum, AnimType const animType, fVector2* const position, fVector2* const defaultAnimPosition);
    explicit Gem(std::shared_ptr<Gem> gemptr);

    void update();
    void setPosition(fVector2& position);
    void setDefaultAnimPosition(fVector2& position);
    void setDefaultAnimState(int const defaultAnimState);
    void startAnimation();
    virtual void onMatched(std::vector<std::vector<std::shared_ptr<Gem>>>& gems, int const row, int const col);
    virtual void draw(WindowHandler* windowHandler);

    fVector2 getCurrentAnimPosition();

    static int const onMatchedChance = 4; //Шанс того что появиться бонус; -1 -> 0% случаев; 10 -> 100% случаев

    bool _toRemove = false;

protected:

    
    virtual void updateShapePosition();
    Color getColor(DefColor const colorEnum);

    

    int _animState;
    int _defaultAnimState;
    AnimType _animType;

    fVector2 _position;
    fVector2 _animPosition;
    fVector2 _defaultAnimPosition;

    DefColor _colorEnum;
    RectangleShape _shape;

private:
    
    
    void updateAnimState();
    float applyEasingFunc(float const t);

    
};

#endif