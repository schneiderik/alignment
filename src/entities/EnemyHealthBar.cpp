#include "EnemyHealthBar.h"

void EnemyHealthBar::onNotify(Enemy enemy, Event event) {
  switch (event) {
    case Event::ENEMY_DAMAGED:
      width_ = (int)ceil(enemy.getPercentHealth() * (float)ENEMY_HEALTH_BAR_WIDTH_MAX),
      break;
  }
}

void EnemyHealthBar::reset() {
  width_ = ENEMY_HEALTH_BAR_WIDTH_MAX;
}

void EnemyHealthBar::render(int x, int y) {
  arduboy.fillRect(
    x,
    y,
    width_,
    ENEMY_HEALTH_BAR_HEIGHT,
    WHITE
  ); 
}
