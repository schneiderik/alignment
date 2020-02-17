#include "WinView.h"
#include "../../Game.h"

void WinView::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) game->reset(); 
}

void WinView::render() {
  sprites.drawOverwrite(21, 3, victoryImage, 0);
  sprites.drawOverwrite(6, 33, winTextImage, 0);    
  sprites.drawOverwrite(53, 46, dividerImage, 0);
  renderNumberAlignCenter(game->score, 64, 54, WHITE);
}
