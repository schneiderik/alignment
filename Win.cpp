#include "Win.h"

void Win::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) resetGame(); 
}

void Win::render() {
  sprites.drawOverwrite(21, 3, victoryImage, 0);
  sprites.drawOverwrite(6, 33, winTextImage, 0);    
  sprites.drawOverwrite(53, 46, dividerImage, 0);
  renderNumberAlignCenter(score, 64, 54, false);
}
