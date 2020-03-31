#ifndef Gem_H
#define Gem_H

#include "../../global.h"

#define GEM_STATE_INACTIVE 0
#define GEM_STATE_FALLING 1
#define GEM_STATE_CLEARING 2
#define GEM_STATE_POPPING 3
#define GEM_STATE_HIDDEN 4

#define GEM_POPPING_ANIMATION_START_FRAME 5
#define GEM_POPPING_ANIMATION_END_FRAME 7

#define GEM_MOVE_X_INCREMENT -3

class Gem {
  public:
    static const int COUNT = 5;

    void init(int, int);   
    void render();
    void update();

    bool isInactive();
    bool isFalling();
    bool isClearing();
    bool isPopping();
    bool isHidden();

    void stop();
    void drop();
    void clear();
    void pop();
    void hide();

    Gem* getNext() const;
    void setNext(Gem*);
    int getX() const;
    int getY() const;
    void setY(int);
    int getType() const;

  private:
    int type_;
    int x_;
    int y_;
    int state_ = GEM_STATE_HIDDEN;
    int xVel_;
    int yVel_;
    Gem* next_;

    void updateX_();
    void updateClear_();
    void updatePop_();
};

#endif
