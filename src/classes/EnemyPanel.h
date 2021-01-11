#ifndef ENEMY_PANEL_H
#define ENEMY_PANEL_H

#include "../../global.h"

#include "./Counter.h"

#define ENEMY_PANEL_HEALTH_BAR_X 2
#define ENEMY_PANEL_HEALTH_BAR_Y 50
#define ENEMY_PANEL_HEALTH_BAR_HEIGHT 1
#define ENEMY_PANEL_HEALTH_BAR_WIDTH 20

#define ENEMY_PANEL_ANIMATION_X 0
#define ENEMY_PANEL_ANIMATION_Y 0

#define ENEMY_PANEL_SPRITE_DATA_LENGTH 2
#define ENEMY_PANEL_SPRITE_DATA_IDLE 0
#define ENEMY_PANEL_SPRITE_DATA_ATTACK 1

#define ENEMY_PANEL_ANIMATION_DATA_LENGTH 3
#define ENEMY_PANEL_ANIMATION_DATA_ATTACK_SPRITE_FRAME_COUNT 0
#define ENEMY_PANEL_ANIMATION_DATA_ATTACK_SPRITE_FRAME_DURATION 1
#define ENEMY_PANEL_ANIMATION_DATA_ATTACK_SPRITE_STRIKE_FRAME 2

#define ENEMY_PANEL_IDLE_SPRITE_FRAME_COUNT 3
#define ENEMY_PANEL_IDLE_SPRITE_FRAME_DURATION 30

struct EnemyPanel
{
  static const int enemyAnimationData[ENEMY_COUNT][ENEMY_PANEL_ANIMATION_DATA_LENGTH];
  static const unsigned char* enemySpriteData[ENEMY_COUNT][ENEMY_PANEL_SPRITE_DATA_LENGTH];

  Counter attackCounter;
  Counter idleCounter;
  bool shouldAttack;
  unsigned char* idleSprite;
  unsigned char* attackSprite;
  int strikeFrame;

  void (*onStrike)();

  void init(uint8_t, void(*)());
  void attack();
  void update();
  void render(int, int, float, float);
  void renderHealthBar(int, int, float, float);
};

#endif
