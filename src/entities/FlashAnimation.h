#ifndef FLASH_ANIMATION_H
#define FLASH_ANIMATION_H

#include "../../global.h"

class FlashAnimation {
  public:
    FlashAnimation(int count, int duration): count_(count), index_(count), duration_(duration) {};

    void run();
    void reset();
    void update();
    bool isVisible();

  private:
    void toggle_();

    int count_;
    int duration_;
    int index_;
    bool visible_ = true;
};

#endif
