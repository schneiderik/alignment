#include "BattleView.h"

#include "Game.h"
#include "StatBar.h"

#define BATTLE_VIEW_STAT_BAR_X 0
#define BATTLE_VIEW_STAT_BAR_Y 0

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
      BATTLE_VIEW_STAT_BAR_Y
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
