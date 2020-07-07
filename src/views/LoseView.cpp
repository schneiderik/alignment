#include "LoseView.h"

void LoseView::handleInput(Game game) {
  if (arduboy.justPressed(A_BUTTON)) {
    game.goToTitleView();
    game.reset();
    game.getAudio().playConfirmSound();
  }
}

void LoseView::render() {
  sprites.drawOverwrite(23, 9, youDiedImage, 0);
  sprites.drawOverwrite(48, 35, tryAgainImage, 0);   
  sprites.drawOverwrite(53, 42, dividerImage, 0);
  renderNumberAlignCenter(game.getPlayer().getScore(), 64, 50, WHITE);
}
