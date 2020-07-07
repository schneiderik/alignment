#include "BattleView.h"
#include "../../Enemy.h"

void BattleView::init(Game game) {
  enemyPanel_.init(game.getCurrentEnemy());
  playerPanel_.init(game.getPlayer());
  puzzle_.init(game);
  attackInterval_.init(ATTACK_INTERVAL_MIN, ATTACK_INTERVAL_MAX);
  setRandomAttackInterval_();
}

void BattleView::handleInput(Game game) {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused_ = !paused_;
  if (paused) return;
  if (arduboy.pressed(LEFT_BUTTON)) puzzle_.enableFastFall();
  if (arduboy.justReleased(LEFT_BUTTON)) puzzle_.disableFastFall();
  if (arduboy.justPressed(UP_BUTTON)) puzzle_.decrementCursor();
  if (arduboy.justPressed(DOWN_BUTTON)) puzzle_.incrementCursor();
  if (arduboy.justPressed(A_BUTTON)) puzzle_.swap();
}

void BattleView::update(Game game) {
  if (paused_) return;

  attackInterval_.update();
  enemyPanel_.update();
  puzzle_.update();

  if (attackInterval_.isActive()) attack_();
}

void BattleView::render(Game game) {
  playerPanel.render(PLAYER_PANEL_X, PLAYER_PANEL_Y);
  enemyPanel_.render(ENEMY_PANEL_X, ENEMY_PANEL_Y);
  puzzle_.render(PUZZLE_X, PUZZLE_Y);
  renderPaused_();
}

void BattleView::navigateTo_(Game game) {
  puzzle_.reset();
  enemyPanel_.reset();
  attackInterval_.reset();
}

void BattleView::attack_() {
  enemyPanel_.attack();

  switch (game.getCurrentEnemy().getType()) {
    case Enemy::SKELETON:
      // puzzle_.slashRandomTopGem();
      break;
    case Enemy::ORC:
      // puzzle_.queueGem();
      break;
    case Enemy::GOLEM:
      // puzzle_.lockWeapons();
      break;
    case Enemy::DEMON:
      // puzzle_.forceFastFall(3000);
      break;
    case Enemy::SORCERER:
      // puzzle_.addRandomGem();
      break;
  }
}

void BattleView::renderPaused_() {
  if (paused_) sprites.drawOverwrite(PAUSED_X, PAUSED_Y, pausedTextImage, 0);
}
