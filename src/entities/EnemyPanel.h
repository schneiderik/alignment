#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#define PORTRAIT_X 0
#define PORTRAIT_Y 0

#define HEALTH_BAR_X 2
#define HEALTH_BAR_Y 50

#include "../../global.h"
#include "../../Enemy.h"
#include "EnemyPortrait.h"
#include "EnemyHealthBar.h"

class EnemyPanel {
  public:
    void init(Enemy);
    void update();
    void render(int, int);
    void reset();

  private:
    EnemyPortrait portrait_;
    EnemyHealthBar healthBar_;
}

#endif
