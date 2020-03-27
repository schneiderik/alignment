#include "Game.h"
#include "Player.h"

void Game::handleInput() {
  switch (state_) {
    case GAME_STATE_TITLE:
      titleView_.handleInput();   
      break;
    case GAME_STATE_INFO:
      infoView_.handleInput();
      break;
    case GAME_STATE_QUEST:
      questView_.handleInput();
      break;
    case GAME_STATE_BATTLE:
      battleView_.handleInput();
      break;
    case GAME_STATE_WIN:
      winView_.handleInput();
      break;
    case GAME_STATE_LOSE:
      loseView_.handleInput();
      break;
  }    
}

void Game::update() {
  switch (state_) {
    case GAME_STATE_QUEST:
      questView_.update();
      break;
    case GAME_STATE_BATTLE:
      battleView_.update();
      break;
  }    
}

void Game::render() {
  switch (state_) {
    case GAME_STATE_TITLE:
      titleView_.render();
      break;
    case GAME_STATE_INFO:
      infoView_.render();
      break;
    case GAME_STATE_QUEST:
      questView_.render();
      break;
    case GAME_STATE_BATTLE:
      battleView_.render();
      break;
    case GAME_STATE_WIN:
      winView_.render();
      break;
    case GAME_STATE_LOSE:
      loseView_.render();
      break;
  }  
}

void Game::reset() {
  enemy->init(Enemy::SKELETON);
  player->reset();
  goToTitleView();
}

void Game::goToTitleView() { state_ = GAME_STATE_TITLE; }
void Game::goToInfoView() { state_ = GAME_STATE_INFO; }
void Game::goToQuestView() { state_ = GAME_STATE_QUEST; }
void Game::goToWinView() { state_ = GAME_STATE_WIN; }
void Game::goToLoseView() { state_ = GAME_STATE_LOSE; }

void Game::goToBattleView() {
  battleView_.reset();
  state_ = GAME_STATE_BATTLE;
}

int Game::getGameSpeed() {
  return fastFall_ ? FAST_FALL_SPEED : INITIAL_GAME_SPEED;
}

void Game::enableFastFall() {
  fastFall_ = true;
}

void Game::disableFastFall() {
  fastFall_ = false;
}
