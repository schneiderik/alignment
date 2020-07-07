#ifndef ENEMY_HEALTH_BAR_H
#define ENEMY_HEALTH_BAR_H

#include "../../Enemy.h"

#define ENEMY_HEALTH_BAR_HEIGHT 1
#define ENEMY_HEALTH_BAR_WIDTH_MAX 20

class EnemyHealthBar {
  public:
    void init(Enemy);
    void render(int, int);

  private:
    Enemy* enemy_ = NULL;
}

#endif
