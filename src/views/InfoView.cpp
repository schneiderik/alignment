#include "InfoView.h"
#include "../../Game.h"

void InfoView::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) {
    game->goToTitleView();
    confirmSound();
  }
}

void InfoView::render() {
  sprites.drawOverwrite(11, 4, infoImage, 0);
}
