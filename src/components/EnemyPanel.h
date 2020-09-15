#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#include "../../global.h"

namespace EnemyPanel
{
  extern bool isStriking;

  void init(uint8_t);
  void attack();
  void update();
  void render(int, int, float, float);
}

#endif
