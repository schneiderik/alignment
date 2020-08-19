#include "InfoView.h"

#include "Game.h"

#define INFO_VIEW_IMAGE_X 11
#define INFO_VIEW_IMAGE_Y 4

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
      INFO_VIEW_IMAGE_X,
      INFO_VIEW_IMAGE_Y,
      infoImage,
      0
    );
  }
}

void InfoView::loop()
{
  handleInput();
  render();
}
