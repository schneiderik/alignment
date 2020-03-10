#include "global.h"
#include "Game.h"
#include "Player.h"
#include "src/collections/WeaponManager.h"
#include "src/collections/GemManager.h"

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);
  
  game = new Game();
  player = new Player();
  enemy = new Enemy();
  weaponManager = new WeaponManager();
  gemManager = new GemManager();
  
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
