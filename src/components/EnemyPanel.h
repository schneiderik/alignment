#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#include "../../global.h"

namespace EnemyPanel
{
  void init(uint8_t);
  void attack();
  void update(void (*)());
  void render(int, int, float, float);
}

#endif
