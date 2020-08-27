#include "EnemyPanel.h"

#define ENEMY_PANEL_HEALTH_BAR_X 2
#define ENEMY_PANEL_HEALTH_BAR_Y 50
#define ENEMY_PANEL_HEALTH_BAR_HEIGHT 1
#define ENEMY_PANEL_HEALTH_BAR_WIDTH 20

#define ENEMY_PANEL_ANIMATION_X 0
#define ENEMY_PANEL_ANIMATION_Y 0

namespace
{
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

void EnemyPanel::render(
  int x,
  int y,
  uint8_t type,
  int health,
  int maxHealth,
  Animation& animation
)
{
  renderHealthBar(
    x + ENEMY_PANEL_HEALTH_BAR_X,
    y + ENEMY_PANEL_HEALTH_BAR_Y,
    health,
    maxHealth
  );

  animation.render(
    x + ENEMY_PANEL_ANIMATION_X,
    y + ENEMY_PANEL_ANIMATION_Y
  );
}
