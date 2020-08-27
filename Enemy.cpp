#include "Enemy.h"

#include "Counter.h"

#define ENEMY_DATA_LENGTH 5
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_WEAPON_MODIFIERS 1

#define ENEMY_IDLE_ANIMATION_FRAME_COUNT 3
#define ENEMY_IDLE_ANIMATION_INTERVAL 30
#define SKELETON_ATTACK_ANIMATION_FRAME_COUNT 5
#define SKELETON_ATTACK_ANIMATION_INTERVAL 20
#define ORC_ATTACK_ANIMATION_FRAME_COUNT 7
#define ORC_ATTACK_ANIMATION_INTERVAL 20
#define GOLEM_ATTACK_ANIMATION_FRAME_COUNT 6
#define GOLEM_ATTACK_ANIMATION_INTERVAL 20
#define DEMON_ATTACK_ANIMATION_FRAME_COUNT 5
#define DEMON_ATTACK_ANIMATION_INTERVAL 20
#define SORCERER_ATTACK_ANIMATION_FRAME_COUNT 7
#define SORCERER_ATTACK_ANIMATION_INTERVAL 15

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

uint8_t Game::Enemy::type;
int Game::Enemy::health;
int Game::Enemy::healthMax;
Animation Game::Enemy::idleAnimation;
Animation Game::Enemy::attackAnimation;

void Game::Enemy::init(uint8_t type)
{
  Game::Enemy::type = type;
  Game::Enemy::health = enemyData[type][ENEMY_DATA_HEALTH];
  Game::Enemy::healthMax = enemyData[type][ENEMY_DATA_HEALTH];

  switch (type)
  {
    case ENEMY_TYPE_SKELETON:
      Game::Enemy::idleAnimation.init(
        skeletonIdleSprite,
        ENEMY_IDLE_ANIMATION_FRAME_COUNT,
        ENEMY_IDLE_ANIMATION_INTERVAL
      );

      Game::Enemy::idleAnimation.alternate();

      Game::Enemy::attackAnimation.init(
        skeletonAttackSprite,
        SKELETON_ATTACK_ANIMATION_FRAME_COUNT,
        SKELETON_ATTACK_ANIMATION_INTERVAL
      );
      break;
    case ENEMY_TYPE_ORC:
      Game::Enemy::idleAnimation.init(
        orcIdleSprite,
        ENEMY_IDLE_ANIMATION_FRAME_COUNT,
        ENEMY_IDLE_ANIMATION_INTERVAL
      );

      Game::Enemy::idleAnimation.alternate();

      Game::Enemy::attackAnimation.init(
        orcAttackSprite,
        ORC_ATTACK_ANIMATION_FRAME_COUNT,
        ORC_ATTACK_ANIMATION_INTERVAL
      );
      break;
    case ENEMY_TYPE_GOLEM:
      Game::Enemy::idleAnimation.init(
        golemIdleSprite,
        ENEMY_IDLE_ANIMATION_FRAME_COUNT,
        ENEMY_IDLE_ANIMATION_INTERVAL
      );

      Game::Enemy::idleAnimation.alternate();

      Game::Enemy::attackAnimation.init(
        golemAttackSprite,
        GOLEM_ATTACK_ANIMATION_FRAME_COUNT,
        GOLEM_ATTACK_ANIMATION_INTERVAL
      );
      break;
    case ENEMY_TYPE_DEMON:
      Game::Enemy::idleAnimation.init(
        demonIdleSprite,
        ENEMY_IDLE_ANIMATION_FRAME_COUNT,
        ENEMY_IDLE_ANIMATION_INTERVAL
      );

      Game::Enemy::idleAnimation.loop();

      Game::Enemy::attackAnimation.init(
        demonAttackSprite,
        DEMON_ATTACK_ANIMATION_FRAME_COUNT,
        DEMON_ATTACK_ANIMATION_INTERVAL
      );
      break;
    case ENEMY_TYPE_SORCERER:
      Game::Enemy::idleAnimation.init(
        sorcererIdleSprite,
        ENEMY_IDLE_ANIMATION_FRAME_COUNT,
        ENEMY_IDLE_ANIMATION_INTERVAL
      );

      Game::Enemy::idleAnimation.alternate();

      Game::Enemy::attackAnimation.init(
        sorcererAttackSprite,
        SORCERER_ATTACK_ANIMATION_FRAME_COUNT,
        SORCERER_ATTACK_ANIMATION_INTERVAL
      );
      break;
  }
}
