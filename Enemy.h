#ifndef ENEMY_H
#define ENEMY_H

#include "global.h";

class Enemy {
  public:
    Enemy();
    
    void set(int);
    void reset();
    void takeDamage(int, int);
    void render();
    void update();

    int type;
    int health;
    int healthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;
    
    int enemyTakeDamageAnimationFrame = ENEMY_TAKE_DAMAGE_ANIMATION_END_FRAME;
    int enemyTakeDamageFlashCount = ENEMY_TAKE_DAMAGE_FLASH_COUNT_MAX;
    int enemyPortraitOffset = 0;
    int enemyPortraitVelocity = 1;
    int enemyTakeDamageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME;
    int enemyTakeDamageIndicatorY = ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y;
    int enemyTakeDamageIndicatorNum = 0;
};

#endif
