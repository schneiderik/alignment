#include "global.h"
#include "Game.h"

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);
  
  game = new Game();
  
  arduboy.clear();
}

void loop() {
  if ((!arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  game->handleInput();
  game->update();
  game->render();
  
  arduboy.display();
}
