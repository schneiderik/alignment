#include "Game.h"

void Game::setState(int state) {
  state_ = state; 
};

void Game::handleInput() {
  switch(state_) {
    case GAME_STATES::GAME_STATE_TITLE:
      title_.handleInput(*this);
      break;
    case GAME_STATES::GAME_STATE_INFO:
      info_.handleInput(*this);
      break;
    case GAME_STATES::GAME_STATE_QUEST:
      quest_.handleInput(*this);
      break;
    case GAME_STATES::GAME_STATE_BATTLE:
      battle_.handleInput(*this);
      break;
  };  
}

void Game::update() {
  switch(state_) {
    case GAME_STATES::GAME_STATE_QUEST:
      quest_.update();
      break;
    case GAME_STATES::GAME_STATE_BATTLE:
      battle_.update(*this);
      break;
  };
};

void Game::render() {
  switch(state_) {
    case GAME_STATES::GAME_STATE_TITLE:
      title_.render();
      break;
    case GAME_STATES::GAME_STATE_INFO:
      info_.render();
      break;
    case GAME_STATES::GAME_STATE_QUEST:
      quest_.render(*this);
      break;
    case GAME_STATES::GAME_STATE_BATTLE:
      battle_.render(*this);
      break;
  };
};
