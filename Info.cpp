#include "Info.h"
#include "Game.h"

void Info::update(Game& game) {
  if (arduboy.justPressed(A_BUTTON)) {
    game.setState(GAME_STATES::GAME_STATE_TITLE);
  }
};

void Info::render() {
   sprites.drawOverwrite(
    INFO_IMAGE_X,
    INFO_IMAGE_Y,
    infoImage,
    0
  );
};
