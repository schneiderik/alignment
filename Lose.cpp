#include "Lose.h"

void Lose::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) resetGame();
}

void Lose::render() {
  sprites.drawOverwrite(23, 9, youDiedImage, 0);
  sprites.drawOverwrite(48, 35, tryAgainImage, 0);   
  sprites.drawOverwrite(53, 42, dividerImage, 0);
  renderNumberAlignCenter(score, 64, 50, false);
}
