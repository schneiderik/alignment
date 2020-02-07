#include "Game.h"

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
