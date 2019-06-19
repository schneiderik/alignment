#include "Enemy.h"

int ENEMIES[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
  {1, 100, 0, 0, 0, 0},
  {2, 200, 0, 0, 0, 0},
  {3, 200, 0, 1, -1, 1},
  {4, 150, -1, -1, 1, 0},
  {5, 250, 1, -1, -1, -1}
};

void Enemy::setEnemy(int type) {
  type_ = type;
  health_ = ENEMIES[type][ENEMY_DATA_HEALTH];
  
  for (int i = 0; i < WEAPON_COUNT; i++) {
    weaponModifiers_[i] = ENEMIES[type][ENEMY_DATA_MODIFIER + i];
  }
}

boolean Enemy::isDead() {
  return health_ <= 0;
}

void Enemy::takeDamage(int attack[WEAPON_COUNT]) {
  for (int i = 0; i < WEAPON_COUNT; i++) {
    health_ -= (attack[i] + weaponModifiers_[i]);
  }

  float percentHealth = health_ / ENEMIES[type_][ENEMY_DATA_HEALTH];
  healthBarWidth_ = percentHealth * ENEMY_HEALTH_WIDTH;
}

void Enemy::render() {
  arduboy.fillRect(
    ENEMY_PANEL_X,
    ENEMY_PANEL_Y,
    ENEMY_PANEL_WIDTH,
    ENEMY_PANEL_HEIGHT
  );

  sprites.drawOverwrite(
    ENEMY_PORTRAIT_X,
    ENEMY_PORTRAIT_Y,
    enemySprite,
    type_
  );

  arduboy.fillRect(
    ENEMY_HEALTH_X,
    ENEMY_HEALTH_Y,
    healthBarWidth_,
    ENEMY_HEALTH_HEIGHT,
    0
  ); 
}
