#include "EnemyPanel.h"

#define ENEMY_PANEL_HEALTH_BAR_X 2
#define ENEMY_PANEL_HEALTH_BAR_Y 50
#define ENEMY_PANEL_HEALTH_BAR_HEIGHT 1
#define ENEMY_PANEL_HEALTH_BAR_WIDTH 20

#define ENEMY_PANEL_ANIMATION_X 0
#define ENEMY_PANEL_ANIMATION_Y 0

namespace
{
  Animation idleAnimation;
  Animation attackAnimation;
  int strikeFrame;
  bool shouldAttack;

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

bool EnemyPanel::didStrike;

void EnemyPanel::init(
  uint8_t type,
  unsigned char* idleSprite,
  int idleSpriteFrameCount,
  int idleSpriteFrameDuration,
  unsigned char* attackSprite,
  int attackSpriteFrameCount,
  int attackSpriteFrameDuration,
  int attackSpriteStrikeFrame
)
{
  idleAnimation.init(
    idleSprite,
    idleSpriteFrameCount,
    idleSpriteFrameDuration
  );

  type == ENEMY_TYPE_DEMON
    ? idleAnimation.loop()
    : idleAnimation.alternate();

  attackAnimation.init(
    attackSprite,
    attackSpriteFrameCount,
    attackSpriteFrameDuration
  );

  strikeFrame = attackSpriteStrikeFrame;
}

void EnemyPanel::update()
{
  if (attackAnimation.running)
  {
    didStrike = false;

    if (attackAnimation.frameJustCompleted(strikeFrame - 1)) {
      didStrike = true;
    }

    attackAnimation.update();
  }
  else
  {
    if (shouldAttack && idleAnimation.frameJustCompleted(0))
    {
      attackAnimation.run();
      shouldAttack = false;
    } 
    else
    {
      idleAnimation.update();
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
  int health,
  int maxHealth
)
{
  renderHealthBar(
    x + ENEMY_PANEL_HEALTH_BAR_X,
    y + ENEMY_PANEL_HEALTH_BAR_Y,
    health,
    maxHealth
  );

  if (attackAnimation.running)
  {
    attackAnimation.render(
      x + ENEMY_PANEL_ANIMATION_X,
      y + ENEMY_PANEL_ANIMATION_Y
    );
  }
  else
  {
    idleAnimation.render(
      x + ENEMY_PANEL_ANIMATION_X,
      y + ENEMY_PANEL_ANIMATION_Y
    );
  }
}
