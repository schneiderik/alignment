#include "Enemy.h"

#include "Animation.h"

#define ENEMY_DATA_LENGTH 8
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_WEAPON_MODIFIERS 1
#define ENEMY_DATA_ATTACK_SPRITE_FRAME_COUNT 5
#define ENEMY_DATA_ATTACK_SPRITE_FRAME_DURATION 6
#define ENEMY_DATA_ATTACK_SPRITE_STRIKE_FRAME 7

#define ENEMY_SPRITE_DATA_LENGTH 2
#define ENEMY_SPRITE_DATA_IDLE 0
#define ENEMY_SPRITE_DATA_ATTACK 1

#define ENEMY_IDLE_SPRITE_FRAME_COUNT 3
#define ENEMY_IDLE_SPRITE_FRAME_DURATION 30

uint8_t Game::CurrentEnemy::type;
int Game::CurrentEnemy::health;
int Game::CurrentEnemy::healthMax;
unsigned char* Game::CurrentEnemy::idleSprite;
int Game::CurrentEnemy::idleSpriteFrameCount;
int Game::CurrentEnemy::idleSpriteFrameDuration;
unsigned char* Game::CurrentEnemy::attackSprite;
int Game::CurrentEnemy::attackSpriteFrameCount;
int Game::CurrentEnemy::attackSpriteFrameDuration;
int Game::CurrentEnemy::attackSpriteStrikeFrame;

namespace
{
  const int enemyData[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
    {100, 0, 0, 0, 0, 5, 15, 2},
    {200, 0, 0, 0, 0, 7, 15, 3},
    {200, -1, 2, -2, 1, 6, 15, 3},
    {150, -1, -1, 2, 0, 5, 20, 3},
    {250, 2, -1, -1, -2, 7, 15, 4}
  };

  const unsigned char* enemySpriteData[ENEMY_COUNT][ENEMY_SPRITE_DATA_LENGTH] = {
    {skeletonIdleSprite, skeletonAttackSprite},
    {orcIdleSprite, orcAttackSprite},
    {golemIdleSprite, golemAttackSprite},
    {demonIdleSprite, demonAttackSprite},
    {sorcererIdleSprite, sorcererAttackSprite}
  };
}

void Game::CurrentEnemy::init(uint8_t type_)
{
  type = type_;
  health = enemyData[type][ENEMY_DATA_HEALTH];
  healthMax = enemyData[type][ENEMY_DATA_HEALTH];
  idleSprite = enemySpriteData[type][ENEMY_SPRITE_DATA_IDLE];
  idleSpriteFrameCount = ENEMY_IDLE_SPRITE_FRAME_COUNT;
  idleSpriteFrameDuration = ENEMY_IDLE_SPRITE_FRAME_DURATION;
  attackSprite = enemySpriteData[type][ENEMY_SPRITE_DATA_ATTACK];
  attackSpriteFrameCount = enemyData[type][ENEMY_DATA_ATTACK_SPRITE_FRAME_COUNT];
  attackSpriteFrameDuration = enemyData[type][ENEMY_DATA_ATTACK_SPRITE_FRAME_DURATION];
  attackSpriteStrikeFrame = enemyData[type][ENEMY_DATA_ATTACK_SPRITE_STRIKE_FRAME];
}
