#include "Enemy.h"
#include "Game.h"

const int Enemy::DATA[COUNT][DATA_LENGTH] = {
  {100, 0, 0, 0, 0},
  {200, 0, 0, 0, 0},
  {200, -1, 2, -2, 1},
  {150, -1, -1, 2, 0},
  {250, 2, -1, -1, -2}
};

Enemy::Enemy() {
  flashAnimation_ = new Animation(
    FLASH_ANIMATION_LOWER_LIMIT,
    FLASH_ANIMATION_UPPER_LIMIT,
    FLASH_ANIMATION_DURATION,
    FLASH_ANIMATION_COUNT,
    FLASH_ANIMATION_LOOP
  );

  shakeAnimation_ = new Animation(
    SHAKE_ANIMATION_LOWER_LIMIT,
    SHAKE_ANIMATION_UPPER_LIMIT,
    SHAKE_ANIMATION_COUNT,
    SHAKE_ANIMATION_DURATION,
    SHAKE_ANIMATION_LOOP
  );

  damageIndicatorAnimation_ = new Animation(
    DAMAGE_INDICATOR_ANIMATION_LOWER_LIMIT,
    DAMAGE_INDICATOR_ANIMATION_UPPER_LIMIT,
    DAMAGE_INDICATOR_ANIMATION_COUNT,
    DAMAGE_INDICATOR_ANIMATION_DURATION,
    DAMAGE_INDICATOR_ANIMATION_LOOP
  );

  idleAnimation_ = new Animation(
    IDLE_ANIMATION_LOWER_LIMIT,
    IDLE_ANIMATION_UPPER_LIMIT,
    IDLE_ANIMATION_SPEED,
    IDLE_ANIMATION_LOOP
  );

  init(SKELETON);
}

void Enemy::init(int type) {
  type_ = type;
  health_ = getHealthData_(type);
  healthBarWidth_ = HEALTH_BAR_WIDTH_MAX;
  flashAnimation_->reset();
  shakeAnimation_->reset();
  damageIndicatorAnimation_->reset();
  idleAnimation_->reset();
}

void Enemy::initNext() {
  init(type_ + 1);
}

void Enemy::update() {
  if (!damageIndicatorAnimation_->isRunning()) damageIndicatorNum_ = 0;

  if (isDead()) {
    if (isLastEnemy()) {
      game->goToWinView();
    } else { 
      initNext();
      game->goToQuestView();
    }
  }

  flashAnimation_->update();
  shakeAnimation_->update();
  damageIndicatorAnimation_->update();
  idleAnimation_->update();
}

void Enemy::render() {
  renderPortrait_();
  renderHealthBar_();
  renderDamageIndicator_();
}

void Enemy::takeDamage(int rawDamage, int weaponType) {
  int damage = rawDamage + getWeaponModifierData_(type_, weaponType);
  
  health_ -= damage;
  healthBarWidth_ = getHealthBarWidth_();
  
  flashAnimation_->run();
  shakeAnimation_->run();
  damageIndicatorAnimation_->run();

  damageIndicatorNum_ += -damage;
}

int Enemy::getType() {
  return type_;
}

bool Enemy::isDead() {
  return health_ <= 0;
}

bool Enemy::isLastEnemy() {
  return type_ == Enemy::LAST_ENEMY;
}

void Enemy::renderPortrait_() {
  if (flashAnimation_->getValue() == 0) {
    if (type_ < ORC) {
      sprites.drawOverwrite(
        PORTRAIT_X + shakeAnimation_->getValue(),
        PORTRAIT_Y,
        skeletonSprite,
        shakeAnimation_->isRunning() ? 9 : idleAnimation_->getValue()
      );
    } else {
      sprites.drawOverwrite(
        PORTRAIT_X + shakeAnimation_->getValue(),
        PORTRAIT_Y,
        enemySprite,
        type_
      );
    }
  }
}

void Enemy::renderHealthBar_() {
  arduboy.fillRect(
    HEALTH_BAR_X,
    HEALTH_BAR_Y,
    healthBarWidth_,
    HEALTH_BAR_HEIGHT,
    WHITE
  ); 
}

void Enemy::renderDamageIndicator_() {
  if (!damageIndicatorAnimation_->isRunning()) return;

  renderIndicator(
    damageIndicatorNum_,
    DAMAGE_INDICATOR_X, 
    DAMAGE_INDICATOR_Y + damageIndicatorAnimation_->getValue(),
    BLACK
  );
}

int Enemy::getHealthBarWidth_() {
  float healthPercent = (float)health_ / (float)getHealthData_(type_);
  float healthBarWidth = healthPercent * (float)HEALTH_BAR_WIDTH_MAX;
  return (int)ceil(healthBarWidth);
}

int Enemy::getHealthData_(int type) {
  return DATA[type][DATA_HEALTH];
}

int Enemy::getWeaponModifierData_(int type, int weaponType) {
  return DATA[type][DATA_WEAPON_MODIFIERS + weaponType];
}
