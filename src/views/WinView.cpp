#include "WinView.h"

void WinView::handleInput(Game game) {
  if (arduboy.justPressed(A_BUTTON)) {
    game.goToTitleView();
    game.reset();
    game.getAudio().playConfirmSound();
  }
}

void WinView::render(Game game) {
  sprites.drawOverwrite(21, 3, victoryImage, 0);
  sprites.drawOverwrite(6, 33, winTextImage, 0);    
  sprites.drawOverwrite(53, 46, dividerImage, 0);
  renderNumberAlignCenter(game.getPlayer().getScore(), 64, 54, WHITE);
}
