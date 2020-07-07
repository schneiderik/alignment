#include "InfoView.h"

void InfoView::handleInput(Game game) {
  if (arduboy.justPressed(A_BUTTON)) {
    game.goToTitleView();
    game.getAudio().playConfirmSound();
  }
}

void InfoView::render(Game game) {
  sprites.drawOverwrite(11, 4, infoImage, 0);
}
