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

boolean Enemy::isFinalBoss() {
  return type_ == LAST_ENEMY;
}

void Enemy::takeDamage() {
}
