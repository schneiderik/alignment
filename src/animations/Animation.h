#ifndef ANIMATION_H
#define ANIMATION_H

#include "../../global.h"

class Animation {
  public:
    Animation();

    void init(int, int, int, int, bool);
    void init(int, int, int, int, int, bool);

    void run();
    void reset();
    void update();
    bool isRunning();
    int getValue();

  private:
    bool isAtLimit_();
    bool isAtUpperLimit_();
    bool isAtLowerLimit_();

    int value_ = 0;
    int count_ = 0;
    int intervalLength_ = 0;
    int intervalCount_ = 0;
    int currentInterval_ = 0;
    int velocity_ = 0;
    int initialValue_ = 0;
    int initialVelocity_ = 0;
    int upperLimit_ = 0;
    int lowerLimit_ = 0;
    bool isLooping_ = false;
};

#endif
