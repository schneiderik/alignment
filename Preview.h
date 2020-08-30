#ifndef PREVIEW_H
#define PREVIEW_H

#include "global.h"

namespace Preview
{
  extern uint8_t gemCount;

  void queueGem();
  void isEmpty();
  void render(uint8_t, uint8_t);
}

#endif
