#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"

class Player {
  public:
    void reset();

    unsigned long int getScore();
    void addScore(int);

    bool isDead();
    void takeDamage();

    int getHealth();
    void resetHealth();

  private:
    unsigned long int score_ = 0;
    int health_ = HEALTH_MAX;
};

#endif
