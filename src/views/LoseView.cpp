#include "LoseView.h"
#include "../../Game.h"
#include "../../Player.h"

void LoseView::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) game->reset();
}

void LoseView::render() {
  sprites.drawOverwrite(23, 9, youDiedImage, 0);
  sprites.drawOverwrite(48, 35, tryAgainImage, 0);   
  sprites.drawOverwrite(53, 42, dividerImage, 0);
  renderNumberAlignCenter(player->getScore(), 64, 50, WHITE);
}
