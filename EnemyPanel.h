#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#include "global.h"

#include "Animation.h"

namespace EnemyPanel
{
  void init();
  void update();
  void render(int, int, uint8_t, int, int, Animation&);
}

#endif
