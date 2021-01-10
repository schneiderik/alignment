#include "EnemyPanel.h"

const int EnemyPanel::enemyAnimationData[ENEMY_COUNT][ENEMY_PANEL_ANIMATION_DATA_LENGTH] = {
  {5, 15, 2},
  {7, 15, 3},
  {6, 15, 3},
  {5, 20, 3},
  {7, 15, 4}
};

const unsigned char* EnemyPanel::enemySpriteData[ENEMY_COUNT][ENEMY_PANEL_SPRITE_DATA_LENGTH] = {
  {skeletonIdleSprite, skeletonAttackSprite},
  {orcIdleSprite, orcAttackSprite},
  {golemIdleSprite, golemAttackSprite},
  {demonIdleSprite, demonAttackSprite},
  {sorcererIdleSprite, sorcererAttackSprite}
};

void EnemyPanel::init(
  uint8_t enemyType,
  void (*onStrike_)()
)
{
  idleCounter.init(
    ENEMY_PANEL_IDLE_SPRITE_FRAME_COUNT,
    ENEMY_PANEL_IDLE_SPRITE_FRAME_DURATION
  );

  onStrike = onStrike_;
  shouldAttack = false;

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


void EnemyPanel::update()
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

void EnemyPanel::renderHealthBar(
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
