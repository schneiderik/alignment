#include "Enemy.h"

Enemy::Enemy() {
  flashAnimation_ = new FlashAnimation(FLASH_COUNT, FLASH_DURATION);

  set(ENEMY_TYPE_SKELETON);
}

void Enemy::set(int i) {
  type = i;
  health = ENEMY_DATA[type][ENEMY_DATA_HEALTH];
  healthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;
}

void Enemy::reset() {
  flashAnimation_->reset();
  damageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME;
  offsetX = 0;
  velocityX = 1;
  damageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME;
  damageIndicatorNum = 0;
}

void Enemy::takeDamage(int rawDamage, int weaponType) {
  int damage = rawDamage + ENEMY_DATA[type][ENEMY_DATA_MODIFIER + weaponType];
  
  health -= damage;
  healthBarWidth = (int)ceil(((float)health / (float)ENEMY_DATA[type][ENEMY_DATA_HEALTH]) * (float)ENEMY_HEALTH_BAR_WIDTH_MAX);
  
  flashAnimation_->run();
  offsetX = 0;
  damageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_START_FRAME;
  damageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_START_FRAME;
  damageIndicatorY = ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y;
  damageIndicatorNum = -damage;
}

void Enemy::update() {
  flashAnimation_->update();
  updateX();
  updateDamageIndicator();
}

void Enemy::updateX() {
  if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_ANIMATION_FRAME_LENGTH)) {
    if (damageAnimationFrame < ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME) {
      if (offsetX > 1) velocityX = -1;
      if (offsetX < -1) velocityX = 1;
      offsetX += velocityX;
      damageAnimationFrame++;
    }
  }  
}

void Enemy::updateDamageIndicator() {
  if (damageIndicatorFrame < ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME) {
    if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_INDICATOR_FRAME_LENGTH)) {
      damageIndicatorY--;      
      damageIndicatorFrame++;
    }
  }  
}

void Enemy::render() {
  renderPortrait();
  renderHealthBar();
  renderDamageIndicator();
}

void Enemy::renderPortrait() {
  if (flashAnimation_->isVisible()) sprites.drawOverwrite(104 + offsetX, 12, enemySprite, type);
}

void Enemy::renderHealthBar() {
  arduboy.fillRect(106, 62, healthBarWidth, 1, 1); 
}

void Enemy::renderDamageIndicator() {
  if (damageIndicatorFrame < ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME) {
    int height = numberSprite[1] + 2;
    int width = numberWidth(damageIndicatorNum) + 4;
    
    arduboy.fillRect(SCREEN_WIDTH - 27 + (width/2), damageIndicatorY - 1, width + 2, height + 2, 1);
    arduboy.fillRect(SCREEN_WIDTH - 26 + (width/2), damageIndicatorY, width, height, 0);
    renderNumberAlignCenter(damageIndicatorNum, 116, damageIndicatorY + 2, false);
  }  
}
