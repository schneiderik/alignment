#include "Info.h"

void Info::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) {
    gameState = GAME_STATE_TITLE;
    confirmSound();
  }
}

void Info::render() {
  sprites.drawOverwrite(11, 4, infoImage, 0);
}
