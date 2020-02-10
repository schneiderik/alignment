#ifndef Gem_H
#define Gem_H

#include "global.h"

#define GEM_STATE_INACTIVE 0
#define GEM_STATE_FALLING 1
#define GEM_STATE_STACKED 2
#define GEM_STATE_CLEARING 3
#define GEM_STATE_POPPING 4
#define GEM_STATE_HIDDEN 5

#define GEM_POPPING_ANIMATION_START_FRAME 5
#define GEM_POPPING_ANIMATION_END_FRAME 7

class Gem {
  public:
    void init(int);   
    void render();
    void update();
    bool updateX();
    void updateY();
    bool updateClear();
    void updatePop();

    bool isInactive();
    bool isFalling();
    bool isStacked();
    bool isClearing();
    bool isPopping();
    bool isHidden();

    Weapon& getWeapon();
    bool belowEndOfRowX();
    bool atEndOfRowX();
    bool belowPreviewThreshold();
    bool matchesLastGemInRow();
    void changeRowIfObstructed(int, int);
    void drop();
    void clear();
    void pop();
    void hide();
    void stack();

    Gem* getNext() const;
    void setNext(Gem*);
    int getRow() const;
    void setRow(int);
    int getType() const;

  private:
    int type_;
    int row_;
    int x_;
    int y_;
    int state_ = GEM_STATE_HIDDEN;
    int xVel_;
    int yVel_;
    Gem* next_;
};

#endif
