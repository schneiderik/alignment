#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"
#include "Hearts.h"
#include "Score.h"

class Player {
  public:
    Player() {};

    void reset();
    bool isDead();
    Hearts hearts;
    Score score;
};

#endif
