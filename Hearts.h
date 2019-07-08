#ifndef HEARTS_H
#define HEARTS_H

#include "global.h"

#define HEARTS_MAX 3
#define HEART_SPACING 1

class Hearts {
  public:
    Hearts() {};

    void lose();
    void gain();
    void reset();
    int get();
    void render(int, int);

  private:
    int num_ = HEARTS_MAX;
};

#endif
