#ifndef GEM_H
#define GEM_H

#define GEM_FALL_INCREMENT 3
#define GEM_FALL_FRAME_LENGTH 5

#define GEM_MOVE_INCREMENT 3
#define GEM_MOVE_FRAME_LENGTH 1

#define GEM_CLEAR_ANIMATION_LENGTH 3
#define GEM_CLEAR_ANIMATION_FRAME_LENGTH 10
#define GEM_CLEAR_ANIMATION_START_INDEX GEM_COUNT
#define GEM_CLEAR_ANIMATION_END_INDEX GEM_CLEAR_ANIMATION_START_INDEX + GEM_CLEAR_ANIMATION_LENGTH - 1

#define GEM_STATE_READY 0
#define GEM_STATE_FALLING 1
#define GEM_STATE_STOPPED 2
#define GEM_STATE_ADJUSTING 3
#define GEM_STATE_CLEARING 4
#define GEM_STATE_HIDDEN 5

#include "global.h"

class Gem {
  public:
    Gem() {};

    void update();
    void render();

    void setType(int);
    int getType();

    void setX(int);
    int getX();
    void setTargetX(int);
    int getTargetX();
    int getXPlusWidth();

    void setY(int);
    int getY();
    void setTargetY(int);

    void ready();
    void drop();
    void stop();
    void adjust();
    void clear();
    void hide();

    int getState();
    bool isReady();
    bool isFalling();
    bool isStopped();
    bool isAdjusting();
    bool isClearing();
    bool isHidden();
    bool isAnimating();

  private:
    int type_ = 0;
    int weaponType_ = 0;
    int state_ = GEM_STATE_HIDDEN;
    int x_ = 0;
    int targetX_ = 0;
    int y_ = 0;
    int targetY_ = 0;
    int frame_ = GEM_CLEAR_ANIMATION_START_INDEX;
    int clearAnimationInterval_ = 0;
    int fallInterval_ = 0;
    int moveInterval_ = 0;

    void updateX_();
    void updateY_();
    void updateClearAnimation_();
};

#endif
