#ifndef Gem_H
#define Gem_H

#include "../../global.h"

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
    static const int STATE_INACTIVE = 0;
    static const int STATE_FALLING = 1;
    static const int STATE_CLEARING = 2;
    static const int STATE_POPPING = 3;
    static const int STATE_HIDDEN = 4;

    const int POPPING_ANIMATION_START_FRAME = 5;
    const int POPPING_ANIMATION_END_FRAME = 7;

    const int MOVE_X_INCREMENT = -3;
    const int MOVE_Y_INCREMENT = 3;

    int type_;
    int x_;
    int y_;
    int state_ = STATE_HIDDEN;
    int xVel_;
    int yVel_;
    Gem* next_;

    void updateX_();
    void updateClear_();
    void updatePop_();
};

#endif
