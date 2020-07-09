#include "BattleView.h"
#include "../../Enemy.h"

void BattleView::init(const Game& game) {
  enemyPanel_.init(game.getCurrentEnemy());
  playerPanel_.init(game.getPlayer());
  puzzle_.init(game);
}

void BattleView::handleInput(const Game& game) {
  if (arduboy.justPressed(RIGHT_BUTTON)) paused_ = !paused_;
  if (paused) return;
  if (arduboy.justPressed(LEFT_BUTTON)) puzzle_.enableFastFall();
  if (arduboy.justReleased(LEFT_BUTTON)) puzzle_.disableFastFall();
  if (arduboy.justPressed(UP_BUTTON)) puzzle_.decrementCursor();
  if (arduboy.justPressed(DOWN_BUTTON)) puzzle_.incrementCursor();
  if (arduboy.justPressed(A_BUTTON)) puzzle_.swap();
}

void BattleView::update(const Game& game) {
  if (paused_) return;

  enemyPanel_.update();
  puzzle_.update();
}

void BattleView::render(const Game& game) {
  playerPanel.render(PLAYER_PANEL_X, PLAYER_PANEL_Y);
  enemyPanel_.render(ENEMY_PANEL_X, ENEMY_PANEL_Y);
  puzzle_.render(PUZZLE_X, PUZZLE_Y);
  renderPaused_();
}

void BattleView::navigateTo_(const Game& game) {
  puzzle_.reset();
  enemyPanel_.reset();
}

void BattleView::renderPaused_() {
  if (paused_) sprites.drawOverwrite(PAUSED_X, PAUSED_Y, pausedTextImage, 0);
}
