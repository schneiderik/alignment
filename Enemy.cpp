#include "Enemy.h"

#define ENEMY_DATA_LENGTH 5
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_WEAPON_MODIFIERS 1

namespace
{
  const int enemyData[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
    {100, 0, 0, 0, 0},
    {200, 0, 0, 0, 0},
    {200, -1, 2, -2, 1},
    {150, -1, -1, 2, 0},
    {250, 2, -1, -1, -2}
  };
}

void Enemy::init(uint8_t type_)
{
  type = type_;
  health = enemyData[type][ENEMY_DATA_HEALTH];
  healthMax = enemyData[type][ENEMY_DATA_HEALTH];
}
