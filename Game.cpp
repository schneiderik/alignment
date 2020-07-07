#include "Game.h"

Game::Game() {
  battleView_.init(*this);
  questView_.init(*this);

  view_ = &titleView_;
}

void Game::handleInput() { view_->handleInput(*this); }

void Game::update() {
  if (player_.isDead()) {
    goToLoseView();
  }

  if (enemy_.isDead()) {
    if (enemy_.isLastEnemy()) {
      goToWinView();
    } else {
      player_.resetHealth();
      enemy_.initNext();
      goToQuestView();
    }
  }

  view_->update(*this);
}

void Game::render() { view_->render(*this); }
void Game::reset() {
  enemy_.init(Enemy::SKELETON);
  player_->reset();
}

void Game::navigateTo(View* view) {
  view_.navigateFrom(*this);
  view_ = view;
  view_.navigateTo(*this);
}

void Game::goToTitleView() { navigateTo(&titleView_); }
void Game::goToInfoView() { navigateTo(&infoView_); }
void Game::goToQuestView() { navigateTo(&questView_); }
void Game::goToWinView() { navigateTo(&winView_); }
void Game::goToLoseView() { navigateTo(&loseView_); }
void Game::goToBattleView() { navigateTo(&battleView_); }

Player Game::getPlayer() { return player_; }
Enemy Game::getCurrentEnemy() { return enemy_; }
Audio Game::getAudio() { return audio_; }
