#ifndef ENEMY_H
#define ENEMY_H

#include "../../global.h";
#include "../animations/FlashAnimation.h";
#include "../animations/BounceAnimation.h";

#define ENEMY_HEALTH_BAR_WIDTH_MAX 20

#define ENEMY_TYPE_SKELETON 0
#define ENEMY_TYPE_ORC 1
#define ENEMY_TYPE_GOLEM 2
#define ENEMY_TYPE_DEMON 3
#define ENEMY_TYPE_SORCERER 4

#define ENEMY_COUNT 5
#define LAST_ENEMY ENEMY_COUNT - 1

#define ENEMY_DATA_LENGTH 7
#define ENEMY_DATA_HEALTH 0
#define ENEMY_DATA_MODIFIER 1
#define ENEMY_DATA_QUEST_X 5
#define ENEMY_DATA_QUEST_Y 6

#define ENEMY_TAKE_DAMAGE_INDICATOR_FRAME_LENGTH 5
#define ENEMY_TAKE_DAMAGE_INDICATOR_START_FRAME 0
#define ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME 6
#define ENEMY_TAKE_DAMAGE_INDICATOR_X 111
#define ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y 36

const int ENEMY_DATA[ENEMY_COUNT][ENEMY_DATA_LENGTH] = {
  {100, 0, 0, 0, 0, 5, 16},
  {200, 0, 0, 0, 0, 29, 31},
  {200, -1, 2, -2, 1, 53, 16},
  {150, -1, -1, 2, 0, 77, 31},
  {250, 2, -1, -1, -2, 101, 16}
};

class Enemy {
  public:
    Enemy();
    
    void set(int);
    void reset();
    void takeDamage(int, int);
    
    void render();
    void renderPortrait();
    void renderHealthBar();
    void renderDamageIndicator();
    
    void update();
    void updateDamageIndicator();

    int type;
    int health;
    int healthBarWidth = ENEMY_HEALTH_BAR_WIDTH_MAX;

    int damageIndicatorFrame = ENEMY_TAKE_DAMAGE_INDICATOR_END_FRAME;
    int damageIndicatorY = ENEMY_TAKE_DAMAGE_INDICATOR_INITIAL_Y;
    int damageIndicatorNum = 0;

  private:
    const int FLASH_COUNT = 3;
    const int FLASH_DURATION = 20;
    const int BOUNCE_COUNT = 2;
    const int BOUNCE_LOWER_LIMIT = -2;
    const int BOUNCE_UPPER_LIMIT = 2;
    const int BOUNCE_DURATION = 40;

    FlashAnimation* flashAnimation_;
    BounceAnimation* bounceAnimation_;
};

#endif
