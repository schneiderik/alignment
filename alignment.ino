#include "global.h"
#include "Game.h"
#include "Enemy.h"
#include "WeaponManager.h"
#include "Title.h"
#include "Info.h"
#include "Quest.h"
#include "Battle.h"
#include "Win.h"
#include "Lose.h"

Title title;
Battle battle;
Info info;
Quest quest;
Win win;
Lose lose;

void setup() {
  arduboy.initRandomSeed();
  arduboy.begin();
  arduboy.setFrameRate(FPS);

  game = new Game();
  enemy = new Enemy();
  weapons = new WeaponManager();
      
  arduboy.clear();
}

void handleInput() {
  switch (game->state) {
    case GAME_STATE_TITLE:
      title.handleInput();   
      break;
    case GAME_STATE_INFO:
      info.handleInput();
      break;
    case GAME_STATE_QUEST:
      quest.handleInput();
      break;
    case GAME_STATE_BATTLE:
      battle.handleInput();
      break;
    case GAME_STATE_WIN:
      win.handleInput();
      break;
    case GAME_STATE_LOSE:
      lose.handleInput();
      break;
  }  
}

void update() {
  switch (game->state) {
    case GAME_STATE_QUEST:
      quest.update();
      break;
    case GAME_STATE_BATTLE:
      battle.update();
      break;
  }  
}

void render() {
  switch (game->state) {
    case GAME_STATE_TITLE:
      title.render();
      break;
    case GAME_STATE_INFO:
      info.render();
      break;
    case GAME_STATE_QUEST:
      quest.render();
      break;
    case GAME_STATE_BATTLE:
      battle.render();
      break;
    case GAME_STATE_WIN:
      win.render();
      break;
    case GAME_STATE_LOSE:
      lose.render();
      break;
  }
}

void loop() {
  if ((!arduboy.nextFrame())) return;

  arduboy.pollButtons();
  arduboy.clear();

  handleInput();
  update();
  render();
  
  arduboy.display();
}
