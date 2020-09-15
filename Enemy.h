#ifndef ENEMY_H
#define ENEMY_H

#include "global.h"

struct Enemy
{
  uint8_t type;
  int health;
  int healthMax;

  void init(uint8_t);
};

#endif
