#ifndef ENEMY_H
#define ENEMY_H

#include "global.h";
#include "src/animations/Animation.h";

#define PORTRAIT_X 104
#define PORTRAIT_Y 12
#define HEALTH_BAR_X 106
#define HEALTH_BAR_Y 62
#define HEALTH_BAR_HEIGHT 1
#define HEALTH_BAR_WIDTH_MAX 20

#define FLASH_ANIMATION_INITIAL_VALUE 0
#define FLASH_ANIMATION_LOWER_LIMIT 0
#define FLASH_ANIMATION_UPPER_LIMIT 1
#define FLASH_ANIMATION_DURATION 40
#define FLASH_ANIMATION_COUNT 3
#define FLASH_ANIMATION_LOOP true

#define SHAKE_ANIMATION_INITIAL_VALUE 0
#define SHAKE_ANIMATION_LOWER_LIMIT -2
#define SHAKE_ANIMATION_UPPER_LIMIT 2
#define SHAKE_ANIMATION_DURATION 40
#define SHAKE_ANIMATION_COUNT 2
#define SHAKE_ANIMATION_LOOP true

#define DAMAGE_INDICATOR_ANIMATION_INITIAL_VALUE 0
#define DAMAGE_INDICATOR_ANIMATION_LOWER_LIMIT 0
#define DAMAGE_INDICATOR_ANIMATION_UPPER_LIMIT -4
#define DAMAGE_INDICATOR_ANIMATION_DURATION 20
#define DAMAGE_INDICATOR_ANIMATION_COUNT 1
#define DAMAGE_INDICATOR_ANIMATION_LOOP false

#define DAMAGE_INDICATOR_Y 46
#define DAMAGE_INDICATOR_X 116

#define IDLE_ANIMATION_INITIAL_VALUE 0
#define IDLE_ANIMATION_LOWER_LIMIT 0
#define IDLE_ANIMATION_UPPER_LIMIT 3
#define IDLE_ANIMATION_SPEED 30
#define IDLE_ANIMATION_LOOP false

#define ATTACK_ANIMATION_INITIAL_VALUE 4
#define ATTACK_ANIMATION_LOWER_LIMIT 4
#define ATTACK_ANIMATION_UPPER_LIMIT 9
#define ATTACK_ANIMATION_DURATION 50
#define ATTACK_ANIMATION_COUNT 1
#define ATTACK_ANIMATION_LOOP false

#define SLASH_ANIMATION_INITIAL_VALUE 0
#define SLASH_ANIMATION_LOWER_LIMIT 0
#define SLASH_ANIMATION_UPPER_LIMIT 3
#define SLASH_ANIMATION_DURATION 20
#define SLASH_ANIMATION_COUNT 1
#define SLASH_ANIMATION_LOOP false

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

    void renderPortrait_();
    void renderHealthBar_();
    void renderDamageIndicator_();
    void updateDamageIndicator_();
    
    int getHealthBarWidth_();
    int getFrame_();
    void setRandomAttackInterval_();
    void attack_();

    Animation* flashAnimation_;
    Animation* shakeAnimation_;
    Animation* damageIndicatorAnimation_;
    Animation* idleAnimation_;
    Animation* attackAnimation_;
    Animation* slashAnimation_;

    int slashX_ = 0;
    int slashY_ = 0;

    int type_;
    int health_;
    int healthBarWidth_ = HEALTH_BAR_WIDTH_MAX;
    int damageIndicatorNum_ = 0;
    int attackFrame_ = 0;
    int attackInterval_ = 0;
};

#endif