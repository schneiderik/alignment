#include "InfoView.h"

#include "Game.h"

#define INFO_VIEW_IMAGE_X 11
#define INFO_VIEW_IMAGE_Y 4

void InfoView::handleInput()
{
  if (arduboy.justPressed(A_BUTTON))
  {
    Game::state = GAME_STATE_TITLE;
  }
}

void InfoView::render()
{
  sprites.drawOverwrite(
    INFO_VIEW_IMAGE_X,
    INFO_VIEW_IMAGE_Y,
    infoImage,
    0
  );
}
