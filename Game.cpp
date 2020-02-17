#include "Game.h"

void Game::handleInput() {
  switch (state) {
    case GAME_STATE_TITLE:
      titleView.handleInput();   
      break;
    case GAME_STATE_INFO:
      infoView.handleInput();
      break;
    case GAME_STATE_QUEST:
      questView.handleInput();
      break;
    case GAME_STATE_BATTLE:
      battleView.handleInput();
      break;
    case GAME_STATE_WIN:
      winView.handleInput();
      break;
    case GAME_STATE_LOSE:
      loseView.handleInput();
      break;
  }    
}

void Game::update() {
  switch (state) {
    case GAME_STATE_QUEST:
      questView.update();
      break;
    case GAME_STATE_BATTLE:
      battleView.update();
      break;
  }    
}

void Game::render() {
  switch (state) {
    case GAME_STATE_TITLE:
      titleView.render();
      break;
    case GAME_STATE_INFO:
      infoView.render();
      break;
    case GAME_STATE_QUEST:
      questView.render();
      break;
    case GAME_STATE_BATTLE:
      battleView.render();
      break;
    case GAME_STATE_WIN:
      winView.render();
      break;
    case GAME_STATE_LOSE:
      loseView.render();
      break;
  }  
}

void Game::reset() {
  resetBattle();
  enemy.init(Enemy::SKELETON);
  score = 0;
  goToTitleView();
}

void Game::resetBattle() {
  health = HEALTH_MAX;
  gems.reset();
  weapons.reset();
}

void Game::goToTitleView() {
  state = GAME_STATE_TITLE;
}

void Game::goToInfoView() {
  state = GAME_STATE_INFO;
}

void Game::goToQuestView() {
  state = GAME_STATE_QUEST;
}

void Game::goToBattleView() {
  state = GAME_STATE_BATTLE;
}

void Game::goToWinView() {
  state = GAME_STATE_WIN;
}

void Game::goToLoseView() {
  state = GAME_STATE_LOSE;
}

void Game::handlePlayerDefeated() {
  if (health > 0) return;
  goToLoseView(); 
  resetBattle(); 
}

void Game::handleEnemyDefeated() {
  if (!enemy.isDead()) return;

  if (enemy.isLastEnemy()) {
    goToWinView();
  } else { 
    enemy.initNext();
    goToQuestView();
  }

  resetBattle();
}
