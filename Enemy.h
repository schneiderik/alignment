#ifndef ENEMY_H
#define ENEMY_H

#include "global.h"

#include "Animation.h"

namespace Game
{
  namespace Enemy
  {
    extern uint8_t type;
    extern int health;
    extern int healthMax;
    extern Animation idleAnimation;
    extern Animation attackAnimation;

    void init(uint8_t);
  }
}

#endif
