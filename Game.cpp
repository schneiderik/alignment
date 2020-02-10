#include "Game.h"

void Game::handleInput() {
  switch (state) {
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

void Game::update() {
  switch (state) {
    case GAME_STATE_QUEST:
      quest.update();
      break;
    case GAME_STATE_BATTLE:
      battle.update();
      break;
  }    
}

void Game::render() {
  switch (state) {
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

void Game::reset() {
  resetBattle();
  enemy.set(ENEMY_TYPE_SKELETON);
  score = 0;
  goToTitle();
}

void Game::resetBattle() {
  health = HEALTH_MAX;
  gems.reset();
  enemy.reset();
  weapons.reset();
}

void Game::goToTitle() {
  state = GAME_STATE_TITLE;
}

void Game::goToInfo() {
  state = GAME_STATE_INFO;
}

void Game::goToQuest() {
  state = GAME_STATE_QUEST;
}

void Game::goToBattle() {
  state = GAME_STATE_BATTLE;
}

void Game::goToWin() {
  state = GAME_STATE_WIN;
}

void Game::goToLose() {
  state = GAME_STATE_LOSE;
}

void Game::handlePlayerDefeated() {
  if (health > 0) return;
  goToLose(); 
  resetBattle(); 
}

void Game::handleEnemyDefeated() {
  if (enemy.health > 0) return;
  if (enemy.type == LAST_ENEMY) {
    goToWin();
  } else { 
    enemy.set(enemy.type + 1);
    goToQuest();
  }
  resetBattle();
}
