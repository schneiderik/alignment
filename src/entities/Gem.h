#ifndef Gem_H
#define Gem_H

#include "../../global.h"
#include "Weapon.h"

class Gem {
  public:
    static const int COUNT = 5;
    static const int Y_OFFSETS[Weapon::COUNT];
    static const int X_OFFSETS[Weapon::GEM_MAX];

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
    static const int STATE_INACTIVE = 0;
    static const int STATE_FALLING = 1;
    static const int STATE_STACKED = 2;
    static const int STATE_CLEARING = 3;
    static const int STATE_POPPING = 4;
    static const int STATE_HIDDEN = 5;

    const int POPPING_ANIMATION_START_FRAME = 5;
    const int POPPING_ANIMATION_END_FRAME = 7;

    int type_;
    int row_;
    int x_;
    int y_;
    int state_ = STATE_HIDDEN;
    int xVel_;
    int yVel_;
    Gem* next_;
};

#endif
