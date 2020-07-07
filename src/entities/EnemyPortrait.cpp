Enemy::Enemy() {
  flashAnimation_.init(
    FLASH_ANIMATION_INITIAL_VALUE,
    FLASH_ANIMATION_LOWER_LIMIT,
    FLASH_ANIMATION_UPPER_LIMIT,
    FLASH_ANIMATION_COUNT,
    FLASH_ANIMATION_DURATION,
    FLASH_ANIMATION_LOOP
  );

  shakeAnimation_.init(
    SHAKE_ANIMATION_INITIAL_VALUE,
    SHAKE_ANIMATION_LOWER_LIMIT,
    SHAKE_ANIMATION_UPPER_LIMIT,
    SHAKE_ANIMATION_COUNT,
    SHAKE_ANIMATION_DURATION,
    SHAKE_ANIMATION_LOOP
  );

  idleAnimation_.init(
    IDLE_ANIMATION_INITIAL_VALUE,
    IDLE_ANIMATION_LOWER_LIMIT,
    IDLE_ANIMATION_UPPER_LIMIT,
    IDLE_ANIMATION_SPEED,
    IDLE_ANIMATION_LOOP
  );

  attackAnimation_.init(
    ATTACK_ANIMATION_INITIAL_VALUE,
    ATTACK_ANIMATION_LOWER_LIMIT,
    ATTACK_ANIMATION_UPPER_LIMIT,
    ATTACK_ANIMATION_COUNT,
    ATTACK_ANIMATION_DURATION,
    ATTACK_ANIMATION_LOOP
  );
}

void Enemy::init(int type) {
  attackFrame_ = 0;
  flashAnimation_.reset();
  shakeAnimation_.reset();
  idleAnimation_.reset();
  slashAnimation_.reset();
}

void Enemy::update() {
  attackAnimation_.update();
  flashAnimation_.update();
  shakeAnimation_.update();
  idleAnimation_.update();
}

void Enemy::renderPortrait_() {
  if (flashAnimation_.getValue() == 0) {
    sprites.drawOverwrite(
      PORTRAIT_X + shakeAnimation_.getValue(),
      PORTRAIT_Y,
      enemySprite,
      getFrame_() + (type_ * 8)
    );
  }
}

int Enemy::getFrame_() {
  if (attackAnimation_.isRunning()) return attackAnimation_.getValue();
  if (shakeAnimation_.isRunning()) return 9;
  return idleAnimation_.getValue();
}

void Enemy::takeDamage(int rawDamage, int weaponType) {
  healthBarWidth_ = getHealthBarWidth_();
  
  flashAnimation_.run();
  shakeAnimation_.run();
}
