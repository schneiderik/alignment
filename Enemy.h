#ifndef ENEMY_H
#define ENEMY_H

#include "global.h"

class Enemy {
  public:
    Enemy();

    void setEnemy();
    boolean isDead();
    void takeDamage(int*);
    void render();

  private:
    int type_;
    int health_;
    int healthBarWidth_ = ENEMY_HEALTH_WIDTH;
    int weaponModifiers_[WEAPON_COUNT];
};

#endif
