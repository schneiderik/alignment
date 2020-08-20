#include "BattleView.h"

#include "Game.h"
#include "StatBar.h"
#include "Enemy.h"

#define BATTLE_VIEW_STAT_BAR_X 0
#define BATTLE_VIEW_STAT_BAR_Y 0

#define BATTLE_VIEW_ENEMY_X 104
#define BATTLE_VIEW_ENEMY_Y 12

namespace
{
  void handleInput()
  {
  }

  void update()
  {
  }

  void render()
  {
    StatBar::render(
      BATTLE_VIEW_STAT_BAR_X,
      BATTLE_VIEW_STAT_BAR_Y,
      Game::playerHealth,
      Game::score
    );

    Enemy::render(
      BATTLE_VIEW_ENEMY_X,
      BATTLE_VIEW_ENEMY_Y,
      Game::enemyType,
      Game::enemyHealth,
      Game::enemyHealthMax
    );
  }
}

void BattleView::init()
{
}

void BattleView::loop()
{
  handleInput();
  update();
  render();
}
