#ifndef BOUNCE_ANIMATION_H
#define BOUNCE_ANIMATION_H

#include "../../global.h"

class BounceAnimation {
  public:
    BounceAnimation(int, int, int);
    BounceAnimation(int, int, int, int);

    void run();
    void reset();
    void update();
    int getOffset();

  private:
    bool isAtLimit_();

    int count_ = 0;
    int intervalLength_ = 0;
    int intervalCount_ = 0;
    int currentInterval_ = 0;
    int offset_ = 0;
    int velocity_ = 1;
    int upperLimit_ = 0;
    int lowerLimit_ = 0;
};

#endif
