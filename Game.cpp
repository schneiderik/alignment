#include "Game.h"
#include "Player.h"

Game::Game() { router_.init(&titleView_); }

void Game::handleInput() { router_.getView().handleInput(); }
void Game::update() { router_.getView().update(); }
void Game::render() { router_.getView().render(); }

void Game::goToTitleView() { router_.navigateTo(&titleView_); }
void Game::goToInfoView() { router_.navigateTo(&infoView_); }
void Game::goToQuestView() { router_.navigateTo(&questView_); }
void Game::goToWinView() { router_.navigateTo(&winView_); }
void Game::goToLoseView() { router_.navigateTo(&loseView_); }
void Game::goToBattleView() { router_.navigateTo(&battleView_); }

int Game::getGameSpeed() {
  return fastFall_ ? FAST_FALL_SPEED : INITIAL_GAME_SPEED;
}

void Game::enableFastFall() {
  fastFall_ = true;
}

void Game::disableFastFall() {
  if (!forcedFastFall_) fastFall_ = false;
}

void Game::forceEnableFastFall() {
  fastFall_ = true;
  forcedFastFall_ = true;
}

void Game::forceDisableFastFall() {
  fastFall_ = false;
  forcedFastFall_ = false;
}
