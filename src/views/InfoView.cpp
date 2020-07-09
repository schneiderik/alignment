#include "InfoView.h"

void InfoView::handleInput(const Game& game) {
  if (arduboy.justPressed(A_BUTTON)) {
    game.goToTitleView();
    game.getAudio().playConfirmSound();
  }
}

void InfoView::render(const Game& game) {
  sprites.drawOverwrite(11, 4, infoImage, 0);
}
