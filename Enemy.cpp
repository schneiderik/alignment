#include "Enemy.h"

const int Enemy::DATA[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
  {100, 0, 0, 0, 0},
  {200, 0, 0, 0, 0},
  {200, -1, 2, -2, 1},
  {150, -1, -1, 2, 0},
  {250, 2, -1, -1, -2}
};

Enemy::Enemy() {
  init(SKELETON);
}

void Enemy::init(int type) {
  type_ = type;
  health_ = getHealthData_(type);
}

void Enemy::initNext() {
  init(type_ + 1);
}

void Enemy::takeDamage(int damage, int weaponType) {
  health_ -= damage + getWeaponModifierData_(type_, weaponType);
}

int Enemy::getType() {
  return type_;
}

int Enemy::getHealth() {
  return health_;
}

int Enemy::getMaxHealth() {
  return getHealthData_(type_);
}

float Enemy::getPercentHealth() {
  return (float)getHealth() / (float)getMaxHealth();
}

bool Enemy::isDead() {
  return health_ <= 0;
}

bool Enemy::isLastEnemy() {
  return type_ == Enemy::LAST_ENEMY;
}

int Enemy::getHealthData_(int type) {
  return DATA[type][ENEMY_DATA_HEALTH];
}

int Enemy::getWeaponModifierData_(int type, int weaponType) {
  return DATA[type][ENEMY_DATA_WEAPON_MODIFIERS + weaponType];
}
