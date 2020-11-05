#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h"
#include "Gem.h"

#define WEAPON_GEMS_MAX 7

struct Weapon
{
  uint8_t type;
  Gem previewGem;
  bool hasPreviewGem = false;
  Gem fallingGem;
  bool hasFallingGem = false;;
  Gem gems[WEAPON_GEMS_MAX];
  int gemCount = 0;
  int clearingGemCount = 0;

  void (*onGemStack)();
  void (*onClear)();
  void (*onCleared)();

  void init(uint8_t, void (*)(), void (*)(), void (*)());
  void dropPreviewGem();
  void queuePreviewGem();
  void stackGem(uint8_t);
  void update();
  void updateClearingGems();
  void swapGems(Weapon&);
  void clearStack();
  void render(uint8_t, uint8_t, bool);
  void clearPreviewGem();
  void clearFallingGem();
  void setFallingGem(uint8_t);
  bool isClearing();
  bool isFull();
  bool fallingGemIsAboveX(int);
  int getGemX(uint8_t);
  int getEndOfStackX();
};

#endif
