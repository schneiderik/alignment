#ifndef GEM_H
#define GEM_H

#define GEM_FALL_INCREMENT 3
#define GEM_ANIMATE_OUT_FRAME_LENGTH 10
#define GEM_ANIMATE_OUT_LENGTH 3
#define GEM_ANIMATE_OUT_START_INDEX GEM_COUNT
#define GEM_ANIMATE_OUT_END_INDEX GEM_ANIMATE_OUT_START_INDEX + GEM_ANIMATE_OUT_LENGTH - 1
#define GEM_STATE_HIDDEN 0
#define GEM_STATE_STOPPED 1
#define GEM_STATE_ACTIVE 2
#define GEM_STATE_ANIMATING_OUT 3

#include "global.h"

class Gem {
  public:
    Gem() {};

    void update();
    void render(int, int);

    void setType(int);
    int getType();

    void activate();
    void stop();
    void hide();
    void animateOut();

    int getState();
    bool isActive();
    bool isStopped();
    bool isHidden();
    bool isAnimatingOut();

  private:
    int type_ = 0;
    int state_ = GEM_STATE_HIDDEN;
    int frame_ = GEM_ANIMATE_OUT_START_INDEX;
    int interval_ = 0;
};

#endif
