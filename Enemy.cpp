#include "Enemy.h"

int ENEMY_DATA[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
  {100, 0, 0, 0, 0},
  {200, 0, 0, 0, 0},
  {200, 0, 1, -1, 1},
  {150, -1, -1, 1, 0},
  {250, 1, -1, -1, -1}
};

Enemy::Enemy() {
  weaponModifiers_ = new int[WEAPON_COUNT];
  set(ENEMY_TYPE_SKELETON);
}

void Enemy::set(int type) {
  type_ = type;
  health_ = ENEMY_DATA[type][ENEMY_DATA_HEALTH];
  
  for (int i = 0; i < WEAPON_COUNT; i++) {
    weaponModifiers_[i] = ENEMY_DATA[type][ENEMY_DATA_MODIFIER + i];
  }
}

int Enemy::getType() {
  return type_;
}

boolean Enemy::isDead() {
  return health_ <= 0;
}

void Enemy::takeDamage() {
}

void Enemy::renderPanel_() {
  arduboy.fillRect(
    ENEMY_PANEL_X,
    ENEMY_PANEL_Y,
    ENEMY_PANEL_WIDTH,
    ENEMY_PANEL_HEIGHT
  ); 
}

void Enemy::renderPortrait_() {
  sprites.drawOverwrite(
    ENEMY_PORTRAIT_X,
    ENEMY_PORTRAIT_Y,
    enemySprite,
    type_
  );  
}

void Enemy::renderHealth_() {
  arduboy.fillRect(
    ENEMY_HEALTH_X,
    ENEMY_HEALTH_Y,
    ENEMY_HEALTH_WIDTH,
    ENEMY_HEALTH_HEIGHT,
    0
  );   
}

void Enemy::render() {
  renderPanel_();
  renderPortrait_();
  renderHealth_();
}
