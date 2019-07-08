#include "Info.h"
#include "Game.h"

void Info::handleInput(Game& game) {
  if (arduboy.justPressed(A_BUTTON)) { game.goToTitleScreen(); }
};

void Info::render() {
   sprites.drawOverwrite(
    INFO_IMAGE_X,
    INFO_IMAGE_Y,
    infoImage,
    0
  );
};
