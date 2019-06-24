#ifndef ENEMY_H
#define ENEMY_H

#include "global.h"

class Enemy {
  public:
    Enemy();

    void set(int);
    int getType();
    boolean isDead();
    void takeDamage();
    void render();

  private:
    int type_;
    int health_;
    int* weaponModifiers_;
    void renderPanel_();
    void renderPortrait_();
    void renderHealth_();
};

#endif
