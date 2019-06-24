#ifndef HEARTS_H
#define HEARTS_H

#include "global.h"

class Hearts {
  public:
    Hearts() {};

    void lose();
    void gain();
    void reset();
    void render(int, int);

  private:
    int num_ = HEARTS_MAX;
};

#endif
