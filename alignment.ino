#include "global.h"

#include "data.h"
#include "sounds.h"
#include "Game.h"
#include "TitleView.h"
#include "InfoView.h"

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();

  arduboy.setFrameRate(FPS);
  arduboy.clear();
}

void loop() {
  if ((!arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  switch (Game::state)
  {
    case GAME_STATE_TITLE:
      TitleView::handleInput();
      TitleView::render();
      break;
    case GAME_STATE_INFO:
      InfoView::handleInput();
      InfoView::render();
      break;
  }
  
  arduboy.display();
}
