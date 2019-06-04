#include <Arduboy2.h>
#include <ArduboyTones.h>

#include "global.h"
#include "Game.h"

Game* pGame = new Game();

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FPS);
    
  arduboy.clear();
}

void loop() {
  if ((!arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  pGame->update();
  pGame->render();
  
  arduboy.display();
}
