void Puzzle::render(int x, int y) {
  renderPreviewDivider_();
  weaponManager_.render();
}

void Puzzle::update() {
  weaponManager_.update();
}


  puzzle_.forceDisableFastFall();
  weaponManager_.reset();

void BattleView::renderPreviewDivider_() {
  arduboy.fillRect(89, 14, 1, 48);
}

int BattleView::getGameSpeed_() {
  return fastFall_ ? FAST_FALL_SPEED : INITIAL_GAME_SPEED;
}

void BattleView::enableFastFall_() {
  fastFall_ = true;
}

void BattleView::disableFastFall_() {
  if (!forcedFastFall_) fastFall_ = false;
}

void BattleView::forceEnableFastFall_() {
  fastFall_ = true;
  forcedFastFall_ = true;
}

void BattleView::forceDisableFastFall_() {
  fastFall_ = false;
  forcedFastFall_ = false;
}


// void Enemy::skeletonAttack_() {
//   Gem* targetGem = weaponManager->popLastGemOfRandomWeapon();
// 
//   if (targetGem != NULL) {
//     slashX_ = targetGem->getX() + 3;
//     slashY_ = targetGem->getY() - 1;
//     slashAnimation_.run();
//   }
// }

// slashAnimation_.init(
//   SLASH_ANIMATION_INITIAL_VALUE,
//   SLASH_ANIMATION_LOWER_LIMIT,
//   SLASH_ANIMATION_UPPER_LIMIT,
//   SLASH_ANIMATION_COUNT,
//   SLASH_ANIMATION_DURATION,
//   SLASH_ANIMATION_LOOP
// );

// if (slashAnimation_.isRunning()) {
//   sprites.drawSelfMasked(
//     slashX_,
//     slashY_,
//     slashSprite,
//     slashAnimation_.getValue()
//   );    
// }
//
// if (slashAnimation_.isRunning()) slashAnimation_.update();

