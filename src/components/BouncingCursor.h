#ifndef BOUNCING_CURSOR_H
#define BOUNCING_CURSOR_H

#include "../../global.h"

namespace BouncingCursor
{
  void init();
  void update();
  void render(uint8_t x, uint8_t y);
}

#endif
