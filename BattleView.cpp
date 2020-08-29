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
    if (arduboy.justPressed(A_BUTTON))
    {
      EnemyPanel::attack();
    }
  }

  void update()
  {
    EnemyPanel::update();
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
      Game::CurrentEnemy::health,
      Game::CurrentEnemy::healthMax
    );
  }
}

void BattleView::init()
{
  EnemyPanel::init(
    Game::CurrentEnemy::type,
    Game::CurrentEnemy::idleSprite,
    Game::CurrentEnemy::idleSpriteFrameCount,
    Game::CurrentEnemy::idleSpriteFrameDuration,
    Game::CurrentEnemy::attackSprite,
    Game::CurrentEnemy::attackSpriteFrameCount,
    Game::CurrentEnemy::attackSpriteFrameDuration
  );
}

void BattleView::loop()
{
  handleInput();
  update();
  render();
}
