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
    FLASH_ANIMATION_INITIAL_VALUE,
    FLASH_ANIMATION_LOWER_LIMIT,
    FLASH_ANIMATION_UPPER_LIMIT,
    FLASH_ANIMATION_COUNT,
    FLASH_ANIMATION_DURATION,
    FLASH_ANIMATION_LOOP
  );

  shakeAnimation_ = new Animation(
    SHAKE_ANIMATION_INITIAL_VALUE,
    SHAKE_ANIMATION_LOWER_LIMIT,
    SHAKE_ANIMATION_UPPER_LIMIT,
    SHAKE_ANIMATION_COUNT,
    SHAKE_ANIMATION_DURATION,
    SHAKE_ANIMATION_LOOP
  );

  damageIndicatorAnimation_ = new Animation(
    DAMAGE_INDICATOR_ANIMATION_INITIAL_VALUE,
    DAMAGE_INDICATOR_ANIMATION_LOWER_LIMIT,
    DAMAGE_INDICATOR_ANIMATION_UPPER_LIMIT,
    DAMAGE_INDICATOR_ANIMATION_COUNT,
    DAMAGE_INDICATOR_ANIMATION_DURATION,
    DAMAGE_INDICATOR_ANIMATION_LOOP
  );

  idleAnimation_ = new Animation(
    IDLE_ANIMATION_INITIAL_VALUE,
    IDLE_ANIMATION_LOWER_LIMIT,
    IDLE_ANIMATION_UPPER_LIMIT,
    IDLE_ANIMATION_SPEED,
    IDLE_ANIMATION_LOOP
  );

  attackAnimation_ = new Animation(
    ATTACK_ANIMATION_INITIAL_VALUE,
    ATTACK_ANIMATION_LOWER_LIMIT,
    ATTACK_ANIMATION_UPPER_LIMIT,
    ATTACK_ANIMATION_COUNT,
    ATTACK_ANIMATION_DURATION,
    ATTACK_ANIMATION_LOOP
  );

  slashAnimation_ = new Animation(
    SLASH_ANIMATION_INITIAL_VALUE,
    SLASH_ANIMATION_LOWER_LIMIT,
    SLASH_ANIMATION_UPPER_LIMIT,
    SLASH_ANIMATION_COUNT,
    SLASH_ANIMATION_DURATION,
    SLASH_ANIMATION_LOOP
  );

  init(SKELETON);
}

void Enemy::init(int type) {
  type_ = type;
  attackFrame_ = 0;
  setRandomAttackInterval_();
  health_ = getHealthData_(type);
  healthBarWidth_ = HEALTH_BAR_WIDTH_MAX;
  flashAnimation_->reset();
  shakeAnimation_->reset();
  damageIndicatorAnimation_->reset();
  idleAnimation_->reset();
  slashAnimation_->reset();
}

void Enemy::initNext() {
  init(type_ + 1);
}

void Enemy::setRandomAttackInterval_() {
  attackInterval_ = random(700, 1200);
}

void Enemy::update() {
  attackAnimation_->update();
  flashAnimation_->update();
  shakeAnimation_->update();
  damageIndicatorAnimation_->update();
  idleAnimation_->update();
  if (slashAnimation_->isRunning()) slashAnimation_->update();

  if (!damageIndicatorAnimation_->isRunning()) damageIndicatorNum_ = 0;

  attackFrame_++;
  if (attackFrame_ == attackInterval_) {
    attack_();
    setRandomAttackInterval_();
    attackFrame_ = 0;
  }

  if (isDead()) {
    if (isLastEnemy()) {
      game->goToWinView();
    } else { 
      initNext();
      game->goToQuestView();
    }
  }
}

void Enemy::render() {
  renderPortrait_();
  renderHealthBar_();
  renderDamageIndicator_();

  if (slashAnimation_->isRunning()) {
    sprites.drawSelfMasked(
      slashX_,
      slashY_,
      slashSprite,
      slashAnimation_->getValue()
    );    
  }
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

void Enemy::attack_() {
  attackAnimation_->run();

  switch(type_) {
    case SKELETON:
      Gem* targetGem = weaponManager->popLastGemOfRandomWeapon();

      if (targetGem != NULL) {
        slashX_ = targetGem->getX() + 4;
        slashY_ = targetGem->getY() - 2;
        slashAnimation_->run();
      }
      break;
  }
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

int Enemy::getFrame_() {
  if (attackAnimation_->isRunning()) return attackAnimation_->getValue();
  if (shakeAnimation_->isRunning()) return 9;
  return idleAnimation_->getValue();
}

void Enemy::renderPortrait_() {
  if (flashAnimation_->getValue() == 0) {
    if (type_ < ORC) {
      sprites.drawOverwrite(
        PORTRAIT_X + shakeAnimation_->getValue(),
        PORTRAIT_Y,
        skeletonSprite,
        getFrame_()
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
