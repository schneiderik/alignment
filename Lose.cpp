#include "Lose.h"
#include "Game.h"

void Lose::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) game->reset();
}

void Lose::render() {
  sprites.drawOverwrite(23, 9, youDiedImage, 0);
  sprites.drawOverwrite(48, 35, tryAgainImage, 0);   
  sprites.drawOverwrite(53, 42, dividerImage, 0);
  renderNumberAlignCenter(game->score, 64, 50, false);
}
