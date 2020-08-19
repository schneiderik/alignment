#include "global.h"

#include "Game.h"

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();

  Game::init();

  arduboy.setFrameRate(FPS);
  arduboy.clear();
}

void loop() {
  if ((!arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  Game::loop();
  
  arduboy.display();
}
