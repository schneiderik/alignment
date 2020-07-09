#include "Puzzle.h"

void Puzzle::render(int x, int y) {
  renderPreviewDivider_(x, y);
  weaponManager_.render(x + PUZZLE_WEAPONS_X, y + PUZZLE_WEAPONS_Y);
}

void Puzzle::update() {
  weaponManager_.update();
}

void Puzzle::onNotify(const Enemy& enemy, Event event) {
  switch (event) {
    case Event::ENEMY_ATTACKING:
      triggerAttackEffect_(enemy);
      break;
  }
}

void Puzzle::triggerAttackEffect_(const Enemy& enemy) {
  switch (enemy.getType()) {
    case Enemy::SKELETON:
      weaponManager_.popLastGemOfRandomWeapon();
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

void Puzzle::reset() {
  forceDisableFastFall();
  weaponManager_.reset();
}

void Puzzle::enableFastFall() {
  fastFall_ = true;
}

void Puzzle::disableFastFall() {
  if (!forcedFastFall_) fastFall_ = false;
}

void Puzzle::forceEnableFastFall() {
  fastFall_ = true;
  forcedFastFall_ = true;
}

void Puzzle::forceDisableFastFall() {
  fastFall_ = false;
  forcedFastFall_ = false;
}

void Puzzle::renderPreviewDivider_(int x, int y) {
  arduboy.fillRect(
    x + PUZZLE_PREVIEW_DIVIDER_X,
    y + PUZZLE_PREVIEW_DIVIDER_Y,
    PUZZLE_PREVIEW_DIVIDER_WIDTH,
    PUZZLE_PREVIEW_DIVIDER_HEIGHT
  );
}

int Puzzle::getGameSpeed_() {
  return fastFall_ ? FAST_FALL_SPEED : INITIAL_GAME_SPEED;
}
