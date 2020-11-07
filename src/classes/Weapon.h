#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h"
#include "Gem.h"

#define WEAPON_GEMS_MAX 7

struct Weapon
{
  uint8_t type;
  int yOffset = 0;
  Gem previewGem;
  bool hasPreviewGem = false;
  Gem fallingGem;
  bool hasFallingGem = false;;
  Gem gems[WEAPON_GEMS_MAX];
  int gemCount = 0;
  int clearingGemCount = 0;

  void (*onGemStack)();
  void (*onMatch)();
  void (*onClear)();
  void (*onCleared)();

  void init(uint8_t, void (*)(), void (*)(), void (*)(), void(*)());
  void dropPreviewGem();
  void queuePreviewGem();
  void handleMatch();
  void stackGem(uint8_t);
  bool hasMatch();
  void update(int);
  void updateClearingGems();
  void swap(Weapon&, int);
  void align();
  void clearStack();
  void render(uint8_t, uint8_t, bool);
  bool isClearing();
  bool isFull();
  bool isAligned();
  bool fallingGemIsAboveX(int);
  int getGemX(uint8_t);
  int getEndOfStackX();
};

#endif
