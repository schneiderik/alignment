#ifndef GEM_H
#define GEM_H

#include "global.h";

#define GEM_STATE_INACTIVE 0
#define GEM_STATE_FALLING 1
#define GEM_STATE_STACKED 2
#define GEM_STATE_CLEARING 3
#define GEM_STATE_CLEARED 4
#define GEM_STATE_POPPING 5
#define GEM_STATE_POPPED 6

#define GEM_POPPING_ANIMATION_START_FRAME 5
#define GEM_POPPING_ANIMATION_END_FRAME 7

class Gem {
  public:    
    int type;
    int row;
    int x;
    int y;
    int velocityX;
    int velocityY;
    int state = GEM_STATE_INACTIVE;

    void render();
    void update();
    void updateX();
    void updateY();
    void updateClear();
    void updatePop();

    bool isInactive();
    bool isFalling();
    bool isStacked();
    bool isClearing();
    bool isCleared();
    bool isPopping();
    bool isPopped();
    
    Weapon& getWeapon();
    bool atEndOfRowX();
    bool belowPreviewThreshold();
    void drop();
    void clear();
    void pop();
};

#endif
