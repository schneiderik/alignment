#ifndef PUZZLE_H
#define PUZZLE_H

#include "../../global.h"

namespace Puzzle
{
  void updateClearingWeapons();
  void updateWeapons();
  void update();
  void incrementCursor();
  void decrementCursor();
  void swap(uint8_t, uint8_t);
  void swapActiveWeapons();
  void swapRandomWeapons();
  void queueRandomPreviewGem();
  void dropPreviewGems();
  bool isClearing();
  void init();
  void render(uint8_t, uint8_t);
}

#endif
