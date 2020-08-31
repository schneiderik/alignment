#include "WinView.h"

#include "../../Game.h"
#include "../components/Number.h"

#define WIN_VIEW_VICTORY_X 21
#define WIN_VIEW_VICTORY_Y 3
#define WIN_VIEW_TEXT_X 6
#define WIN_VIEW_TEXT_Y 33
#define WIN_VIEW_DIVIDER_X 53
#define WIN_VIEW_DIVIDER_Y 46
#define WIN_VIEW_SCORE_X 64
#define WIN_VIEW_SCORE_Y 54

namespace
{
  void handleInput()
  {
    if (arduboy.justPressed(A_BUTTON))
    {
      Game::goToTitleView();
    }
  }

  void render()
  {
    sprites.drawOverwrite(
      WIN_VIEW_VICTORY_X,
      WIN_VIEW_VICTORY_Y,
      victoryImage,
      0
    );

    sprites.drawOverwrite(
      WIN_VIEW_TEXT_X,
      WIN_VIEW_TEXT_Y,
      winTextImage,
      0
    );

    sprites.drawOverwrite(
      WIN_VIEW_DIVIDER_X,
      WIN_VIEW_DIVIDER_Y,
      dividerImage,
      0
    );

    Number::render(
      Game::score,
      WIN_VIEW_SCORE_X,
      WIN_VIEW_SCORE_Y,
      ALIGN_CENTER,
      WHITE
    );
  }
}

void WinView::loop()
{
  handleInput();
  render();
}
