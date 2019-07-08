#ifndef SCORE_H
#define SCORE_H

#include "global.h"

#define NUMBER_SPACING 2

class Score {
  public:
    Score() {};

    unsigned long int get();
    void increase();
    void reset();
    void render(int, int);

  private:
    unsigned long int value_ = 0;
};

#endif
