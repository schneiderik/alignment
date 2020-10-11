#ifndef WEAPON_H
#define WEAPON_H

#include "global.h"

#define WEAPON_GEMS_MAX 7

struct Weapon
{
  uint8_t type;
  int previewGem = -1;
  int fallingGem = -1;
  int fallingGemX = 0;
  int gems[WEAPON_GEMS_MAX];
  int gemCount = 0;

  void init(uint8_t);
  void dropPreviewGem();
  void queuePreviewGem();
  void stackGem(uint8_t);
  void update();
  void render(uint8_t, uint8_t, bool);
  void clearPreviewGem();
  void clearFallingGem();
  void setFallingGem(uint8_t);
  bool hasPreviewGem();
  bool hasFallingGem();
};

#endif
