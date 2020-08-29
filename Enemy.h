#ifndef ENEMY_H
#define ENEMY_H

#include "global.h"

#include "Animation.h"

namespace Game
{
  namespace CurrentEnemy
  {
    extern uint8_t type;
    extern int health;
    extern int healthMax;
    extern unsigned char* idleSprite;
    extern int idleSpriteFrameCount;
    extern int idleSpriteFrameDuration;
    extern unsigned char* attackSprite;
    extern int attackSpriteFrameCount;
    extern int attackSpriteFrameDuration;
    extern int attackSpriteStrikeFrame;

    void init(uint8_t);
  }
}

#endif
