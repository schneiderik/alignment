#ifndef ENEMY_H
#define ENEMY_H

#include "global.h";
#include "src/animations/Animation.h";

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

    const int FLASH_ANIMATION_INITIAL_VALUE = 0;
    const int FLASH_ANIMATION_LOWER_LIMIT = 0;
    const int FLASH_ANIMATION_UPPER_LIMIT = 1;
    const int FLASH_ANIMATION_DURATION = 40;
    const int FLASH_ANIMATION_COUNT = 3;
    const bool FLASH_ANIMATION_LOOP = true;
    
    const int SHAKE_ANIMATION_INITIAL_VALUE = 0;
    const int SHAKE_ANIMATION_LOWER_LIMIT = -2;
    const int SHAKE_ANIMATION_UPPER_LIMIT = 2;
    const int SHAKE_ANIMATION_DURATION = 40;
    const int SHAKE_ANIMATION_COUNT = 2;
    const bool SHAKE_ANIMATION_LOOP = true;

    const int DAMAGE_INDICATOR_ANIMATION_INITIAL_VALUE = 0;
    const int DAMAGE_INDICATOR_ANIMATION_LOWER_LIMIT = 0;
    const int DAMAGE_INDICATOR_ANIMATION_UPPER_LIMIT = -4;
    const int DAMAGE_INDICATOR_ANIMATION_DURATION = 20;
    const int DAMAGE_INDICATOR_ANIMATION_COUNT = 1;
    const bool DAMAGE_INDICATOR_ANIMATION_LOOP = false;

    const int DAMAGE_INDICATOR_Y = 46;
    const int DAMAGE_INDICATOR_X = 116;

    const int IDLE_ANIMATION_INITIAL_VALUE = 0;
    const int IDLE_ANIMATION_LOWER_LIMIT = 0;
    const int IDLE_ANIMATION_UPPER_LIMIT = 3;
    const int IDLE_ANIMATION_SPEED = 30;
    const bool IDLE_ANIMATION_LOOP = false;

    const int ATTACK_ANIMATION_INITIAL_VALUE = 4;
    const int ATTACK_ANIMATION_LOWER_LIMIT = 4;
    const int ATTACK_ANIMATION_UPPER_LIMIT = 9;
    const int ATTACK_ANIMATION_DURATION = 50;
    const int ATTACK_ANIMATION_COUNT = 1;
    const bool ATTACK_ANIMATION_LOOP = false;

    void renderPortrait_();
    void renderHealthBar_();
    void renderDamageIndicator_();
    void updateDamageIndicator_();
    
    int getHealthBarWidth_();
    int getFrame_();
    void setRandomAttackInterval_();

    Animation* flashAnimation_;
    Animation* shakeAnimation_;
    Animation* damageIndicatorAnimation_;
    Animation* idleAnimation_;
    Animation* attackAnimation_;

    int type_;
    int health_;
    int healthBarWidth_ = HEALTH_BAR_WIDTH_MAX;
    int damageIndicatorNum_ = 0;
    int attackFrame_ = 0;
    int attackInterval_ = 0;
};

#endif
