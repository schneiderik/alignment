#include "Game.h"

void Game::handleInput() {
  switch(state_) {
    case GAME_STATE_TITLE:
      title.handleInput(*this);
      break;
    case GAME_STATE_INFO:
      info.handleInput(*this);
      break;
    case GAME_STATE_QUEST:
      quest.handleInput(*this);
      break;
    case GAME_STATE_BATTLE:
      battle.handleInput(*this);
      break;
  };  
}

void Game::update() {
  switch(state_) {
    case GAME_STATE_QUEST:
      quest.update();
      break;
    case GAME_STATE_BATTLE:
      battle.update(*this);
      break;
  };
};

void Game::render() {
  switch(state_) {
    case GAME_STATE_TITLE:
      title.render();
      break;
    case GAME_STATE_INFO:
      info.render();
      break;
    case GAME_STATE_QUEST:
      quest.render(*this);
      break;
    case GAME_STATE_BATTLE:
      battle.render(*this);
      break;
  };
};

void Game::goToTitleScreen() {
  state_ = GAME_STATE_TITLE;
}

void Game::goToInfoScreen() {
  state_ = GAME_STATE_INFO;
}

void Game::goToQuestScreen() {
  state_ = GAME_STATE_QUEST;
}

void Game::goToBattleScreen() {
  state_ = GAME_STATE_BATTLE;
}

void Game::goToLoseScreen() {
  state_ = GAME_STATE_LOSE;
}

void Game::goToWinScreen() {
  state_ = GAME_STATE_WIN;
}

void Game::defeatEnemy() {
  if (enemy.isFinalBoss()) {
    goToWinScreen();
  } else { 
    enemy.set(enemy.getType() + 1);
    goToQuestScreen();
  }
}

