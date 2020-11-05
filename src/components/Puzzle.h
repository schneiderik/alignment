#ifndef PUZZLE_H
#define PUZZLE_H

#include "../../global.h"

namespace Puzzle
{
  void handleWeaponGemStack();
  void handleWeaponClear();
  void handleWeaponCleared();
  void handleWeaponMatch();
  void updateClearingWeapons();
  void updateWeapons();
  void update();
  void incrementCursor();
  void decrementCursor();
  void swap(uint8_t, uint8_t);
  void swapActiveWeapons();
  void swapRandomWeapons();
  void queueRandomPreviewGem();
  void stackRandomGem();
  void dropPreviewGems();
  void enableFastFall();
  void disableFastFall();
  int getSpeed();
  bool isClearing();
  void init(void (*)(), void (*)(), void (*)());
  void render(uint8_t, uint8_t);
}

#endif
