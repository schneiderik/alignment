#ifndef WEAPON_H
#define WEAPON_H

#include "global.h"

struct Weapon
{
  uint8_t type;
  int previewGem = -1;

  void init(uint8_t);
  void render(uint8_t, uint8_t, bool);
};

#endif
