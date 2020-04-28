#include "Game.h"
#include "Player.h"

void Game::handleInput() { view_->handleInput(); }
void Game::update() { view_->update(); }
void Game::render() { view_->render(); }

void Game::reset() {
  enemy->init(Enemy::SKELETON);
  player->reset();
  goToTitleView();
}

void Game::goToTitleView() { view_ = &titleView_; }
void Game::goToInfoView() { view_ = &infoView_; }
void Game::goToQuestView() { view_ = &questView_; }
void Game::goToWinView() { view_ = &winView_; }
void Game::goToLoseView() { view_ = &loseView_; }
void Game::goToBattleView() { view_ = &battleView_; battleView_.reset(); }

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
