#include "BattleView.h"

#include "Game.h"
#include "StatBar.h"
#include "EnemyPanel.h"

#define BATTLE_VIEW_STAT_BAR_X 0
#define BATTLE_VIEW_STAT_BAR_Y 0

#define BATTLE_VIEW_ENEMY_PANEL_X 104
#define BATTLE_VIEW_ENEMY_PANEL_Y 12

namespace
{
  void handleInput()
  {
  }

  void update()
  {
    Game::Enemy::idleAnimation.update();
  }

  void render()
  {
    StatBar::render(
      BATTLE_VIEW_STAT_BAR_X,
      BATTLE_VIEW_STAT_BAR_Y,
      Game::playerHealth,
      Game::score
    );

    EnemyPanel::render(
      BATTLE_VIEW_ENEMY_PANEL_X,
      BATTLE_VIEW_ENEMY_PANEL_Y,
      Game::Enemy::type,
      Game::Enemy::health,
      Game::Enemy::healthMax,
      Game::Enemy::idleAnimation
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
