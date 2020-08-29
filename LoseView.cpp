#include "LoseView.h"

#include "Game.h"
#include "Number.h"

#define LOSE_VIEW_YOU_DIED_X 23
#define LOSE_VIEW_YOU_DIED_Y 9
#define LOSE_VIEW_TRY_AGAIN_X 48
#define LOSE_VIEW_TRY_AGAIN_Y 35
#define LOSE_VIEW_DIVIDER_X 53
#define LOSE_VIEW_DIVIDER_Y 42
#define LOSE_VIEW_SCORE_X 64
#define LOSE_VIEW_SCORE_Y 50

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
      LOSE_VIEW_YOU_DIED_X,
      LOSE_VIEW_YOU_DIED_Y,
      youDiedImage,
      0
    );

    sprites.drawOverwrite(
      LOSE_VIEW_TRY_AGAIN_X,
      LOSE_VIEW_TRY_AGAIN_Y,
      tryAgainImage,
      0
    );

    sprites.drawOverwrite(
      LOSE_VIEW_DIVIDER_X,
      LOSE_VIEW_DIVIDER_Y,
      dividerImage,
      0
    );

    Number::render(
      Game::score,
      LOSE_VIEW_SCORE_X,
      LOSE_VIEW_SCORE_Y,
      ALIGN_CENTER,
      WHITE
    );
  }
}

void LoseView::loop()
{
  handleInput();
  render();
}
