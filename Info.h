#ifndef INFO_H
#define INFO_H

#include "global.h"

#define INFO_IMAGE_X 11
#define INFO_IMAGE_Y 4

class Info {
  public:
    Info() {};

    void handleInput(Game&);
    void render();
};

#endif
