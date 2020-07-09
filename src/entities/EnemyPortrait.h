#ifndef ENEMY_PORTRAIT_H
#define ENEMY_PORTRAIT_H

#define ATTACK_INTERVAL_MIN 700
#define ATTACK_INTERVAL_MAX 1200

#define ENEMY_FRAME_COUNT 9
#define ENEMY_DAMAGE_FRAME 9
#define ENEMY_ATTACK_EFFECT_FRAME 3

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

#include "../../global.h"
#include "../../Event.h"
#include "../../Observer.h"
#include "../../Subject.h"
#include "Interval.h"

class EnemyPortrait: public Observer: public Subject {
  public:
    void init(Enemy);
    void update();
    void render(int, int);
    void reset();

    virtual void onNotify(const Enemy&, Event) override;

  private:
    Enemy* enemy_ = NULL;
    Interval attackInterval_;
    int frame_ = 0;

    void updateFrame_();
};

#endif
