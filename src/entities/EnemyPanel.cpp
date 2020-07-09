#include "EnemyPanel.h"

void EnemyPanel::init(const Enemy& enemy) {
  portrait_.init(enemy);
}

void EnemyPanel::update() {
  portrait_.update();
}

void EnemyPanel::render(int x, int y) {
  portrait_.render(x + PORTRAIT_X, y + PORTRAIT_Y);
  healthBar_.render(x + HEALTH_BAR_X, y + HEALTH_BAR_Y);
}

void EnemyPanel::reset() {
  healthBar_.reset();
  portrait_.reset();
}
