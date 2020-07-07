#include "EnemyHealthBar.h"

void EnemyHealthBar::init(Enemy enemy) {
  enemy_ = &enemy;
}

void EnemyHealthBar::render(int x, int y) {
  arduboy.fillRect(
    x,
    y,
    (int)ceil(enemy_.getPercentHealth() * (float)ENEMY_HEALTH_BAR_WIDTH_MAX),
    ENEMY_HEALTH_BAR_HEIGHT,
    WHITE
  ); 
}
