#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#include "../../global.h"

namespace EnemyPanel
{
  void init(uint8_t, void(*)());
  void attack();
  void update();
  void render(int, int, float, float);
}

#endif
