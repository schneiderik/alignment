#include "EnemyPanel.h"

#include "../../Counter.h"

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

namespace
{
  Counter attackCounter;
  Counter idleCounter;
  bool shouldAttack;
  unsigned char* idleSprite;
  unsigned char* attackSprite;
  int strikeFrame;

  const int enemyAnimationData[ENEMY_COUNT][ENEMY_PANEL_ANIMATION_DATA_LENGTH] = {
    {5, 15, 2},
    {7, 15, 3},
    {6, 15, 3},
    {5, 20, 3},
    {7, 15, 4}
  };

  const unsigned char* enemySpriteData[ENEMY_COUNT][ENEMY_PANEL_SPRITE_DATA_LENGTH] = {
    {skeletonIdleSprite, skeletonAttackSprite},
    {orcIdleSprite, orcAttackSprite},
    {golemIdleSprite, golemAttackSprite},
    {demonIdleSprite, demonAttackSprite},
    {sorcererIdleSprite, sorcererAttackSprite}
  };

  void renderHealthBar(
    int x,
    int y,
    float health,
    float maxHealth
  )
  {
    float percentHealth = health / maxHealth;
    int width = ceil(percentHealth * ENEMY_PANEL_HEALTH_BAR_WIDTH);

    arduboy.fillRect(
      x,
      y,
      width,
      ENEMY_PANEL_HEALTH_BAR_HEIGHT,
      WHITE
    ); 
  }
}

void EnemyPanel::update(void (*onStrike)())
{
  if (attackCounter.running)
  {
    if (attackCounter.frameJustCompleted(strikeFrame - 1))
    {
      onStrike();
    }

    attackCounter.update();
  }
  else
  {
    if (shouldAttack && idleCounter.frameJustCompleted(0))
    {
      attackCounter.run();
      shouldAttack = false;
    } 
    else
    {
      idleCounter.update();
    }
  }
}

void EnemyPanel::init(
  uint8_t enemyType
)
{
  idleCounter.init(
    ENEMY_PANEL_IDLE_SPRITE_FRAME_COUNT,
    ENEMY_PANEL_IDLE_SPRITE_FRAME_DURATION
  );

  enemyType == ENEMY_TYPE_DEMON
    ? idleCounter.loop()
    : idleCounter.alternate();

  attackCounter.init(
    enemyAnimationData[enemyType][ENEMY_PANEL_ANIMATION_DATA_ATTACK_SPRITE_FRAME_COUNT],
    enemyAnimationData[enemyType][ENEMY_PANEL_ANIMATION_DATA_ATTACK_SPRITE_FRAME_DURATION]
  );

  idleSprite = enemySpriteData[enemyType][ENEMY_PANEL_SPRITE_DATA_IDLE];
  attackSprite = enemySpriteData[enemyType][ENEMY_PANEL_SPRITE_DATA_ATTACK];
  strikeFrame = enemyAnimationData[enemyType][ENEMY_PANEL_ANIMATION_DATA_ATTACK_SPRITE_STRIKE_FRAME];
}

void EnemyPanel::attack()
{
  shouldAttack = true;
}

void EnemyPanel::render(
  int x,
  int y,
  float health,
  float maxHealth
)
{
  renderHealthBar(
    x + ENEMY_PANEL_HEALTH_BAR_X,
    y + ENEMY_PANEL_HEALTH_BAR_Y,
    health,
    maxHealth
  );

  sprites.drawOverwrite(
    x + ENEMY_PANEL_ANIMATION_X,
    y + ENEMY_PANEL_ANIMATION_Y,
    attackCounter.running
      ? attackSprite
      : idleSprite,
    attackCounter.running
      ? attackCounter.frame
      : idleCounter.frame
  );
}
