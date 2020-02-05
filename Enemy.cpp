#include "Enemy.h"

Enemy::Enemy() {
  set(ENEMY_TYPE_SKELETON);
}

void Enemy::set(int i) {
  type = i;
  health = ENEMY_DATA[type][ENEMY_DATA_HEALTH];
  healthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;
}

void Enemy::reset() {
  enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME;
  enemyTakeDamageFlashCount = ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX;
  enemyPortraitOffset = 0;
  enemyPortraitVelocity = 1;
  enemyTakeDamageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME;
  enemyTakeDamageIndicatorNum = 0;
}

void Enemy::takeDamage(int rawDamage, int weaponType) {
  int damage = rawDamage + ENEMY_DATA[type][ENEMY_DATA_MODIFIER + weaponType];
  
  health -= damage;
  healthBarWidth = (int)ceil(((float)health / (float)ENEMY_DATA[type][ENEMY_DATA_HEALTH]) * (float)ENEMY_HEALTH_BAR_WIDTH_MAX);
  
  enemyTakeDamageFlashCount = 0;
  enemyPortraitOffset = 0;
  enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_START_FRAME;
  enemyTakeDamageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_START_FRAME;
  enemyTakeDamageIndicatorY = ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y;
  enemyTakeDamageIndicatorNum = -damage;
}

void Enemy::update() {
  if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_FLASH_LENGTH) && enemyTakeDamageFlashCount < ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX) enemyTakeDamageFlashCount++;

  if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_ANIMATION_FRAME_LENGTH)) {
    if (enemyTakeDamageAnimationFrame < ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME) {
      if (enemyPortraitOffset > 1) enemyPortraitVelocity = -1;
      if (enemyPortraitOffset < -1) enemyPortraitVelocity = 1;
      enemyPortraitOffset += enemyPortraitVelocity;
      enemyTakeDamageAnimationFrame++;
    }
  }

  if (enemyTakeDamageIndicatorFrame < ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME) {
    if (arduboy.everyXFrames(ENEMY_TAKE_DAMAGE_INDICATOR_FRAME_LENGTH)) {
      enemyTakeDamageIndicatorY--;      
      enemyTakeDamageIndicatorFrame++;
    }
  }  
}

void Enemy::render() {
  // Render Enemy Portrait
  if (enemyTakeDamageFlashCount == ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX || enemyTakeDamageFlashCount % 2) {
    sprites.drawOverwrite(104 + enemyPortraitOffset, 12, enemySprite, type);
  }

  //Render Enemy Damage
  if (enemyTakeDamageIndicatorFrame < ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME) {
    int height = numberSprite[1] + 2;
    int width = numberWidth(enemyTakeDamageIndicatorNum) + 4;
    
    arduboy.fillRect(SCREEN_WIDTH - 27 + (width/2), enemyTakeDamageIndicatorY - 1, width + 2, height + 2, 1);
    arduboy.fillRect(SCREEN_WIDTH - 26 + (width/2), enemyTakeDamageIndicatorY, width, height, 0);
    renderNumberAlignCenter(enemyTakeDamageIndicatorNum, 116, enemyTakeDamageIndicatorY + 2, false);
  }

  // Render Enemy Health
  arduboy.fillRect(106, 62, healthBarWidth, 1, 1);  
}
