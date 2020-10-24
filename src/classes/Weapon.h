#ifndef WEAPON_H
#define WEAPON_H

#include "../../global.h"

#define WEAPON_GEMS_MAX 7
#define WEAPON_CLEARING_GEM_DATA_LENGTH 4

struct Weapon
{
  uint8_t type;
  int clearingGemData[WEAPON_GEMS_MAX][WEAPON_CLEARING_GEM_DATA_LENGTH];
  int previewGem = -1;
  int fallingGem = -1;
  int fallingGemX = 0;
  int gems[WEAPON_GEMS_MAX];
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
  void clearStack();
  void render(uint8_t, uint8_t, bool);
  void clearPreviewGem();
  void clearFallingGem();
  void setFallingGem(uint8_t);
  bool hasPreviewGem();
  bool hasFallingGem();
  bool isClearing();
  bool isFull();
  bool fallingGemIsAboveX(int);
  int getGemX(uint8_t);
  int getEndOfStackX();
};

#endif
