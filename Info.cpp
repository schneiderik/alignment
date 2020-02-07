#include "Info.h"
#include "Game.h"

void Info::handleInput() {
  if (arduboy.justPressed(A_BUTTON)) {
    game->goToTitle();
    confirmSound();
  }
}

void Info::render() {
  sprites.drawOverwrite(11, 4, infoImage, 0);
}
