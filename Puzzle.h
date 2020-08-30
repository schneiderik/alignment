#ifndef PUZZLE_H
#define PUZZLE_H

#include "global.h"

namespace Puzzle
{
  void update();
  void incrementCursor();
  void decrementCursor();
  void swap();
  void swap(uint8_t, uint8_t);
  void queuePreviewGem();
  void init();
  void render(uint8_t, uint8_t);
}

#endif
