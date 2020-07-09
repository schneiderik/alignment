#include "EnemyPortrait.h"

void EnemyPortrait::init(Enemy enemy) {
  enemy_ = &enemy;

  attackInterval_.init(ATTACK_INTERVAL_MIN, ATTACK_INTERVAL_MAX);

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

void EnemyPortrait::update() {
  attackInterval_.update();

  if (attackInterval_.isActive()) attackAnimation_.run();

  attackAnimation_.update();
  flashAnimation_.update();
  shakeAnimation_.update();
  idleAnimation_.update();

  if (attackAnimation_.getValue() == ENEMY_ATTACK_EFFECT_FRAME) {
    notify(*enemy_, Event::ENEMY_ATTACKING);
  }

  updateFrame_();
}

void EnemyPortrait::render(int x, int y) {
  if (flashAnimation_.getValue() == 0) {
    sprites.drawOverwrite(
      x + shakeAnimation_.getValue(),
      y,
      enemySprite,
      frame_;
    );
  }
}

void EnemyPortrait::reset() {
  attackInterval_.reset();
  attackAnimation_.reset();
  flashAnimation_.reset();
  shakeAnimation_.reset();
  idleAnimation_.reset();
}

void EnemyPortrait::onNotify(Enemy enemy, Event event) {
  switch (event) {
    case Event::ENEMY_DAMAGED:
      flashAnimation_.run();
      shakeAnimation_.run();
      break;
  }
}

void EnemyPortrait::updateFrame_() {
  int frame = idleAnimation_.getValue();

  if (attackAnimation_.isRunning()) {
    frame = attackAnimation_.getValue();
  } else if (shakeAnimation_.isRunning()) {
    frame = ENEMY_DAMAGE_FRAME;
  }

  frame_ = frame + (enemy_->getType() * ENEMY_FRAME_COUNT);
}
