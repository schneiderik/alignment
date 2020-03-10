#ifndef ENEMY_H
#define ENEMY_H

#include "global.h";
#include "src/animations/FlashAnimation.h";
#include "src/animations/TranslateAnimation.h";

class Enemy {
  public:
    static const int SKELETON = 0;
    static const int ORC = 1;
    static const int GOLEM = 2;
    static const int DEMON = 3;
    static const int SORCERER = 4;
    static const int COUNT = 5;

    Enemy();
    
    void init(int);
    void initNext();
    void update();
    void render();

    void takeDamage(int, int);
    int getType();
    bool isDead();
    bool isLastEnemy();

  private:
    static const int LAST_ENEMY = COUNT - 1;

    static const int DATA_LENGTH = 5;
    static const int DATA_HEALTH = 0;
    static const int DATA_WEAPON_MODIFIERS = 1;
    static const int DATA[COUNT][DATA_LENGTH];

    static int getHealthData_(int);
    static int getWeaponModifierData_(int, int);

    const int PORTRAIT_X = 104;
    const int PORTRAIT_Y = 12;
    const int HEALTH_BAR_X = 106;
    const int HEALTH_BAR_Y = 62;
    const int HEALTH_BAR_HEIGHT = 1;
    const int HEALTH_BAR_WIDTH_MAX = 20;
    const int FLASH_ANIMATION_COUNT = 3;
    const int FLASH_ANIMATION_DURATION = 20;
    const int SHAKE_ANIMATION_LOWER_LIMIT = -2;
    const int SHAKE_ANIMATION_UPPER_LIMIT = 2;
    const int SHAKE_ANIMATION_DURATION = 40;
    const int SHAKE_ANIMATION_COUNT = 2;
    const int SHAKE_ANIMATION_LOOP = true;
    const int DAMAGE_INDICATOR_ANIMATION_LOWER_LIMIT = 0;
    const int DAMAGE_INDICATOR_ANIMATION_UPPER_LIMIT = -4;
    const int DAMAGE_INDICATOR_ANIMATION_DURATION = 20;
    const int DAMAGE_INDICATOR_ANIMATION_COUNT = 1;
    const int DAMAGE_INDICATOR_ANIMATION_LOOP = false;
    const int DAMAGE_INDICATOR_Y = 46;
    const int DAMAGE_INDICATOR_X = 116;

    void renderPortrait_();
    void renderHealthBar_();
    void renderDamageIndicator_();
    void updateDamageIndicator_();
    
    int getHealthBarWidth_();

    FlashAnimation* flashAnimation_;
    TranslateAnimation* shakeAnimation_;
    TranslateAnimation* damageIndicatorAnimation_;
    TranslateAnimation* idleAnimation_;

    int type_;
    int health_;
    int healthBarWidth_ = HEALTH_BAR_WIDTH_MAX;
    int damageIndicatorNum_ = 0;
};

#endif
