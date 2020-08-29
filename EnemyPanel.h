#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#include "global.h"

#include "Animation.h"

namespace EnemyPanel
{
  void init(uint8_t, unsigned char*, int, int, unsigned char*, int, int);
  void update();
  void attack();
  void render(int, int, int, int);
}

#endif
